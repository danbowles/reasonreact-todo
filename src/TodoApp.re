type action =
  | Navigate(TodoFooter.showingState)
  | ToggleItem(Task.task)
  | Destroy(Task.task)
  | NewTodoEnterKeyDown
  | NewTodoOtherKeyDown
  | UpdateNewTodoText(string)
  | Edit(Task.task)
  | CancelEdit
  | SaveEdit(Task.task, string)
  | AddTodoItem;

type state = {
  route: TodoFooter.showingState,
  tasks: list(Task.task),
  newTaskText: string,
  editing: option(int),
};

let taskId = ref(0);
/* This is getting called twice on first click */
let newTask = (state) => {
  taskId := taskId^ + 1;
  let trimmed = String.trim(state.newTaskText);
  String.length(trimmed) === 0
    ? state
    : {
      ...state,
      tasks: [
        {
          id: taskId^,
          title: String.trim(state.newTaskText),
          completed: false,
          archived: false,
        },
        ...state.tasks,
      ],
      newTaskText: "",
    };
}

/* Util */
let str = ReasonReact.string;

let getRouteFromUrl = (path) =>
  switch (path) {
    | ["completed"] => TodoFooter.CompletedTodos;
    | ["active"] => ActiveTodos;
    | ["archived"] => ArchivedTodos;
    | _ => AllTodos;
    };

[@react.component]
let make = () => {
  /* Reducer */
  let (state, dispatch) = React.useReducer(
    (state, action) =>
      switch (action) {
      | Navigate(route) => { ...state, route }
      | AddTodoItem => newTask(state)
      | NewTodoEnterKeyDown => newTask(state)
      | NewTodoOtherKeyDown => state
      | Destroy(task) => {
        let tasks = List.filter((item) => item !== task, state.tasks);
        { ...state, tasks };
      }
      | UpdateNewTodoText(newTaskText) => { ...state, newTaskText }
      | ToggleItem(task) => {
        let tasks = List.map(
          (item) =>
            item === task ? { ...item, completed: !item.completed } : item,
          state.tasks
        );
        { ...state, tasks }
      }
      | Edit(todo) => {
        ...state,
        editing: Some(todo.id)
      }
      | CancelEdit => { ...state, editing: None }
      | SaveEdit(taskToSave, textToSave) => {
        let tasks = List.map(
          (task) => task === taskToSave
            ? { ...task, title: textToSave }
            : task,
          state.tasks
        );
        { ...state, tasks: tasks, editing: None }
      }
      },
    /* Initial State */
    {
      route: AllTodos,
      tasks: [],
      newTaskText: "",
      editing: None,
    }
  );

  let {editing, tasks} = state;

  React.useEffect0(() => {
    let watcherID = ReasonReact.Router.watchUrl(({ path }) =>
      dispatch(Navigate(getRouteFromUrl(path)))
    );
    Some(() => ReasonReact.Router.unwatchUrl(watcherID));
  });

  let itemCount = List.length(tasks);
  let completedCount = tasks
    |> List.filter((item: Task.task) => item.completed && !item.archived)
    |> List.length;
  let activeCount = itemCount - completedCount;
  let archivedCount = tasks
  |> List.filter((item: Task.task) => item.archived)
  |> List.length; 
  
  let tasks =
    tasks
    |> List.filter((task) => {
      Task.(
        switch(state.route) {
        | AllTodos => true
        | CompletedTodos => task.completed
        | ActiveTodos => !task.completed && !task.archived
        | ArchivedTodos => task.archived
        }
      )
    })
    |> List.map((task) => {
      let editing =
        switch(editing) {
        | None => false
        | Some(editing) => editing === Task.(task.id)
        };
      <Task
        onChange=((_) => dispatch(ToggleItem(task)))
        onDestroy=((_) => dispatch(Destroy(task)))
        onEdit=((_) => dispatch(Edit(task)))
        onCancel=((_) => dispatch(CancelEdit))
        onSave=((editText) => dispatch(SaveEdit(task, editText)))
        task
        editing
      />;
    })
    |> Array.of_list
    |> React.array;

  <div>
    <h1>{str("Todo App")}</h1>
    <input
      type_="text"
      placeholder="What needs doin'?"
      value=state.newTaskText
      onKeyDown=(
        (event) =>
          if (ReactEvent.Keyboard.keyCode(event) === 13) {
            ReactEvent.Keyboard.preventDefault(event);
            dispatch(NewTodoEnterKeyDown);
          } else {
            dispatch(NewTodoOtherKeyDown);
          }
        )
        onChange=(
          (event) =>
            dispatch(UpdateNewTodoText(ReactEvent.Form.target(event)##value))
        )
        autoFocus=true
    />
    <button onClick=((_) => dispatch(AddTodoItem))>
      (str("Add Item"))
    </button>
    <ul>
      tasks
    </ul>
    <TodoFooter
      route=state.route
      itemCount
      completedCount
      activeCount
      archivedCount
    />
  </div>;
};
