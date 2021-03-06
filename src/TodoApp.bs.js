// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var $$String = require("bs-platform/lib/js/string.js");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");
var Task$ReactHooksTemplate = require("./Task.bs.js");
var TodoFooter$ReactHooksTemplate = require("./TodoFooter.bs.js");

var taskId = /* record */[/* contents */0];

function newTask(state) {
  taskId[0] = taskId[0] + 1 | 0;
  var trimmed = $$String.trim(state[/* newTaskText */2]);
  var match = trimmed.length === 0;
  if (match) {
    return state;
  } else {
    return /* record */[
            /* route */state[/* route */0],
            /* tasks : :: */[
              /* record */[
                /* id */taskId[0],
                /* title */$$String.trim(state[/* newTaskText */2]),
                /* completed */false,
                /* archived */false
              ],
              state[/* tasks */1]
            ],
            /* newTaskText */"",
            /* editing */state[/* editing */3]
          ];
  }
}

function str(prim) {
  return prim;
}

function getRouteFromUrl(path) {
  if (path) {
    switch (path[0]) {
      case "active" : 
          if (path[1]) {
            return /* AllTodos */0;
          } else {
            return /* ActiveTodos */1;
          }
      case "archived" : 
          if (path[1]) {
            return /* AllTodos */0;
          } else {
            return /* ArchivedTodos */3;
          }
      case "completed" : 
          if (path[1]) {
            return /* AllTodos */0;
          } else {
            return /* CompletedTodos */2;
          }
      default:
        return /* AllTodos */0;
    }
  } else {
    return /* AllTodos */0;
  }
}

function TodoApp(Props) {
  var match = React.useReducer((function (state, action) {
          if (typeof action === "number") {
            switch (action) {
              case 1 : 
                  return state;
              case 2 : 
                  return /* record */[
                          /* route */state[/* route */0],
                          /* tasks */state[/* tasks */1],
                          /* newTaskText */state[/* newTaskText */2],
                          /* editing */undefined
                        ];
              case 0 : 
              case 3 : 
                  return newTask(state);
              
            }
          } else {
            switch (action.tag | 0) {
              case 0 : 
                  return /* record */[
                          /* route */action[0],
                          /* tasks */state[/* tasks */1],
                          /* newTaskText */state[/* newTaskText */2],
                          /* editing */state[/* editing */3]
                        ];
              case 1 : 
                  var task = action[0];
                  var tasks = List.map((function (item) {
                          var match = item === task;
                          if (match) {
                            return /* record */[
                                    /* id */item[/* id */0],
                                    /* title */item[/* title */1],
                                    /* completed */!item[/* completed */2],
                                    /* archived */item[/* archived */3]
                                  ];
                          } else {
                            return item;
                          }
                        }), state[/* tasks */1]);
                  return /* record */[
                          /* route */state[/* route */0],
                          /* tasks */tasks,
                          /* newTaskText */state[/* newTaskText */2],
                          /* editing */state[/* editing */3]
                        ];
              case 2 : 
                  var task$1 = action[0];
                  var tasks$1 = List.filter((function (item) {
                            return item !== task$1;
                          }))(state[/* tasks */1]);
                  return /* record */[
                          /* route */state[/* route */0],
                          /* tasks */tasks$1,
                          /* newTaskText */state[/* newTaskText */2],
                          /* editing */state[/* editing */3]
                        ];
              case 3 : 
                  return /* record */[
                          /* route */state[/* route */0],
                          /* tasks */state[/* tasks */1],
                          /* newTaskText */action[0],
                          /* editing */state[/* editing */3]
                        ];
              case 4 : 
                  return /* record */[
                          /* route */state[/* route */0],
                          /* tasks */state[/* tasks */1],
                          /* newTaskText */state[/* newTaskText */2],
                          /* editing */action[0][/* id */0]
                        ];
              case 5 : 
                  var textToSave = action[1];
                  var taskToSave = action[0];
                  var tasks$2 = List.map((function (task) {
                          var match = task === taskToSave;
                          if (match) {
                            return /* record */[
                                    /* id */task[/* id */0],
                                    /* title */textToSave,
                                    /* completed */task[/* completed */2],
                                    /* archived */task[/* archived */3]
                                  ];
                          } else {
                            return task;
                          }
                        }), state[/* tasks */1]);
                  return /* record */[
                          /* route */state[/* route */0],
                          /* tasks */tasks$2,
                          /* newTaskText */state[/* newTaskText */2],
                          /* editing */undefined
                        ];
              
            }
          }
        }), /* record */[
        /* route : AllTodos */0,
        /* tasks : [] */0,
        /* newTaskText */"",
        /* editing */undefined
      ]);
  var state = match[0];
  var editing = state[/* editing */3];
  var tasks = state[/* tasks */1];
  var dispatch = match[1];
  React.useEffect((function () {
          var watcherID = ReasonReactRouter.watchUrl((function (param) {
                  return Curry._1(dispatch, /* Navigate */Block.__(0, [getRouteFromUrl(param[/* path */0])]));
                }));
          return (function (param) {
                    return ReasonReactRouter.unwatchUrl(watcherID);
                  });
        }), ([]));
  var itemCount = List.length(tasks);
  var completedCount = List.length(List.filter((function (item) {
                if (item[/* completed */2]) {
                  return !item[/* archived */3];
                } else {
                  return false;
                }
              }))(tasks));
  var activeCount = itemCount - completedCount | 0;
  var archivedCount = List.length(List.filter((function (item) {
                return item[/* archived */3];
              }))(tasks));
  var tasks$1 = $$Array.of_list(List.map((function (task) {
              var editing$1 = editing !== undefined ? editing === task[/* id */0] : false;
              return React.createElement(Task$ReactHooksTemplate.make, {
                          task: task,
                          onDestroy: (function (param) {
                              return Curry._1(dispatch, /* Destroy */Block.__(2, [task]));
                            }),
                          onEdit: (function (param) {
                              return Curry._1(dispatch, /* Edit */Block.__(4, [task]));
                            }),
                          onChange: (function (param) {
                              return Curry._1(dispatch, /* ToggleItem */Block.__(1, [task]));
                            }),
                          editing: editing$1,
                          onCancel: (function (param) {
                              return Curry._1(dispatch, /* CancelEdit */2);
                            }),
                          onSave: (function (editText) {
                              return Curry._1(dispatch, /* SaveEdit */Block.__(5, [
                                            task,
                                            editText
                                          ]));
                            })
                        });
            }), List.filter((function (task) {
                    var match = state[/* route */0];
                    switch (match) {
                      case 0 : 
                          return true;
                      case 1 : 
                          if (task[/* completed */2]) {
                            return false;
                          } else {
                            return !task[/* archived */3];
                          }
                      case 2 : 
                          return task[/* completed */2];
                      case 3 : 
                          return task[/* archived */3];
                      
                    }
                  }))(tasks)));
  return React.createElement("div", undefined, React.createElement("h1", undefined, "Todo App"), React.createElement("input", {
                  autoFocus: true,
                  placeholder: "What needs doin'?",
                  type: "text",
                  value: state[/* newTaskText */2],
                  onKeyDown: (function ($$event) {
                      if ($$event.keyCode === 13) {
                        $$event.preventDefault();
                        return Curry._1(dispatch, /* NewTodoEnterKeyDown */0);
                      } else {
                        return Curry._1(dispatch, /* NewTodoOtherKeyDown */1);
                      }
                    }),
                  onChange: (function ($$event) {
                      return Curry._1(dispatch, /* UpdateNewTodoText */Block.__(3, [$$event.target.value]));
                    })
                }), React.createElement("button", {
                  onClick: (function (param) {
                      return Curry._1(dispatch, /* AddTodoItem */3);
                    })
                }, "Add Item"), React.createElement("ul", undefined, tasks$1), React.createElement(TodoFooter$ReactHooksTemplate.make, {
                  route: state[/* route */0],
                  itemCount: itemCount,
                  completedCount: completedCount,
                  activeCount: activeCount,
                  archivedCount: archivedCount
                }));
}

var make = TodoApp;

exports.taskId = taskId;
exports.newTask = newTask;
exports.str = str;
exports.getRouteFromUrl = getRouteFromUrl;
exports.make = make;
/* react Not a pure module */
