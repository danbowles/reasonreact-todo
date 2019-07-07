let str = ReasonReact.string;
let trim = String.trim;

type action =
  | Edit
  | Change(string)
  | KeyDown(int);

type state = {
  editText: string,
};

type task = {
  id: int,
  title: string,
  completed: bool,
  archived: bool,
};

[@react.component]
let make = (~task, ~onDestroy, ~onEdit, ~onChange, ~editing, ~onCancel, ~onSave) => {
  let onSubmitHelper = (state) => {
    switch(trim(state.editText)) {
    | "" => {
      onDestroy();
      state;
    }
    | nonEmpty => {
      onSave(nonEmpty);
      { editText: nonEmpty };
    }
    }
  }
  /* Reducer */
  let (state, dispatch) = React.useReducer(
    (state, action) =>
      switch (action) {
      | Edit => { editText: task.title }
      | Change(editText) => { editText: editText }
      | KeyDown(13) => onSubmitHelper(state)
      | KeyDown(27) => {
        onCancel();
        { editText: task.title };
      }
      | KeyDown(_) => state
      },
      {
        editText: "",
      }
    );
  <li className="item" key=(string_of_int(task.id))>
    <input
      type_="checkbox"
      checked=(task.completed)
      onChange
    />
    <label
      onDoubleClick=((_event) => {
        onEdit();
        dispatch(Edit);
      })
    >
      (
        editing
          ? <input
              type_="text"
              value=(state.editText)
              autoFocus=true
              onChange=(
                (event) => dispatch(Change(ReactEvent.Form.target(event)##value))
              )
              onKeyDown=(
                (event) => dispatch(KeyDown(ReactEvent.Keyboard.which(event)))
              )
            />
          : str(task.title)
      )
    </label>
    <button onClick=((_) => onDestroy())>(str("Delete"))</button>
  </li>
}