type showingState =
  | AllTodos
  | ActiveTodos
  | CompletedTodos
  | ArchivedTodos;

[@react.component]
let make = (
  ~route,
  ~itemCount,
  ~completedCount,
  ~activeCount,
  ~archivedCount
) => {
  let push = (path, event) => {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReactRouter.push(path);
  };

  let (all, active, completed, archived) =
    switch(route) {
    | AllTodos => ("selected", "", "", "")
    | ActiveTodos => ("", "selected", "", "")
    | CompletedTodos => ("", "", "selected", "")
    | ArchivedTodos => ("", "", "", "selected")
    };

  <div>
    <ul>
      <li>
        <a onClick=(push("/"))>
          (ReasonReact.string("All (" ++ string_of_int(itemCount) ++ ") " ++ all))
        </a>
      </li>
      <li>
        <a onClick=(push("/active"))>
          (ReasonReact.string("Active (" ++ string_of_int(activeCount) ++ ") " ++ active))
        </a>
      </li>
      <li>
        <a onClick=(push("completed"))>
          {ReasonReact.string("Completed (" ++ string_of_int(completedCount) ++ ") " ++ completed)}
        </a>
      </li>
      <li>
        <a onClick=(push("archived"))>
          {ReasonReact.string("Archived (" ++ string_of_int(archivedCount) ++ ") " ++ archived)}
        </a>
      </li>
    </ul>
  </div>;
};
