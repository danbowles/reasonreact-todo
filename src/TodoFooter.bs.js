// Generated by BUCKLESCRIPT VERSION 5.0.3, PLEASE EDIT WITH CARE
'use strict';

var React = require("react");
var ReasonReactRouter = require("reason-react/src/ReasonReactRouter.js");

function TodoFooter(Props) {
  var route = Props.route;
  var itemCount = Props.itemCount;
  var completedCount = Props.completedCount;
  var activeCount = Props.activeCount;
  var archivedCount = Props.archivedCount;
  var push = function (path, $$event) {
    $$event.preventDefault();
    return ReasonReactRouter.push(path);
  };
  var match;
  switch (route) {
    case 0 : 
        match = /* tuple */[
          "selected",
          "",
          "",
          ""
        ];
        break;
    case 1 : 
        match = /* tuple */[
          "",
          "selected",
          "",
          ""
        ];
        break;
    case 2 : 
        match = /* tuple */[
          "",
          "",
          "selected",
          ""
        ];
        break;
    case 3 : 
        match = /* tuple */[
          "",
          "",
          "",
          "selected"
        ];
        break;
    
  }
  return React.createElement("div", undefined, React.createElement("ul", undefined, React.createElement("li", undefined, React.createElement("a", {
                          onClick: (function (param) {
                              return push("/", param);
                            })
                        }, "All (" + (String(itemCount) + (") " + match[0])))), React.createElement("li", undefined, React.createElement("a", {
                          onClick: (function (param) {
                              return push("/active", param);
                            })
                        }, "Active (" + (String(activeCount) + (") " + match[1])))), React.createElement("li", undefined, React.createElement("a", {
                          onClick: (function (param) {
                              return push("completed", param);
                            })
                        }, "Completed (" + (String(completedCount) + (") " + match[2])))), React.createElement("li", undefined, React.createElement("a", {
                          onClick: (function (param) {
                              return push("archived", param);
                            })
                        }, "Archived (" + (String(archivedCount) + (") " + match[3]))))));
}

var make = TodoFooter;

exports.make = make;
/* react Not a pure module */
