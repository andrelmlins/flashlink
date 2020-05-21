[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(LinkReducer.reducer, LinkReducer.initialState);
  let (name, setName) = React.useState(() => "");
  let (link, setLink) = React.useState(() => "");
  let (description, setDescription) = React.useState(() => "");

  React.useEffect0(() => {
    dispatch(ShowList);

    None;
  });

  <div>
    <table>
      <thead>
        <tr>
          <th> {React.string("Name")} </th>
          <th> {React.string("Link")} </th>
          <th> {React.string("Description")} </th>
        </tr>
      </thead>
      <tbody>
        {state.list
         ->Belt.Array.map(item =>
             <tr>
               <td> {React.string(item.name)} </td>
               <td> {React.string(item.link)} </td>
               <td> {React.string(item.description)} </td>
             </tr>
           )
         ->React.array}
        <tr>
          <td>
            <input
              value=name
              onChange={e => {
                let value = ReactEvent.Form.target(e)##value;
                setName(_ => value);
              }}
            />
          </td>
          <td>
            <input
              value=link
              onChange={e => {
                let value = ReactEvent.Form.target(e)##value;
                setLink(_ => value);
              }}
            />
          </td>
          <td>
            <input
              value=description
              onChange={e => {
                let value = ReactEvent.Form.target(e)##value;
                setDescription(_ => value);
              }}
            />
          </td>
          <td>
            <button
              onClick={_ => {dispatch(Create(name, link, description))}}>
              {React.string("Salvar")}
            </button>
          </td>
        </tr>
      </tbody>
    </table>
  </div>;
};