[@react.component]
let make = (~showing) => {
  <div>
    <h1>{ReasonReact.string(showing)}</h1>
  </div>;
};
