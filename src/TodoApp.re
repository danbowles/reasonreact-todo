type taskType = {
  id: int,
  title: string,
  completed: bool,
  archived: bool,
};

type action =
  | Navigate(TodoFooter.showingState)
  | ToggleItem(taskType)
  | Destroy(taskType)
  | NewTodoEnterKeyDown
  | NewTodoOtherKeyDown
  | UpdateNewTodoText(string)
  | Edit(taskType)
  | AddTodoItem;

  type state = {
  route: TodoFooter.showingState,
  tasks: list(taskType),
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

module Task = {
  [@react.component]
  let make = (~task, ~onDestroy, ~onEdit, ~onChange, ~editing) => {
    <li className="item" key=(string_of_int(task.id))>
      <input
        type_="checkbox"
        checked=(task.completed)
        onChange
      />
      <label
        onDoubleClick=((_event) => onEdit())
      >
        (str(task.title ++ string_of_bool(editing)))
      </label>
      <button onClick=(onDestroy)>(str("Delete"))</button>
    </li>
  }
}

[@react.component]
let make = () => {
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
    |> List.filter(item => item.completed && !item.archived)
    |> List.length;
  let activeCount = itemCount - completedCount;
  let archivedCount = tasks
  |> List.filter(item => item.archived)
  |> List.length; 
  
  let tasks =
    tasks
    |> List.filter((task) => {
      switch(state.route) {
      | AllTodos => true
      | CompletedTodos => task.completed
      | ActiveTodos => !task.completed && !task.archived
      | ArchivedTodos => task.archived
      }
    })
    |> List.map((task) => {
      let editing =
        switch(state.editing) {
        | None => false
        | Some(editing) => editing === task.id
        };
      <Task
        onChange=((_) => dispatch(ToggleItem(task)))
        onDestroy=((_) => dispatch(Destroy(task)))
        onEdit=((_) => dispatch(Edit(task)))
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
