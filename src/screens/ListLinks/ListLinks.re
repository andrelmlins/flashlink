[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(LinkReducer.reducer, LinkReducer.initialState);
  let (name, setName) = React.useState(() => "");
  let (url, setUrl) = React.useState(() => "");
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
         ->Belt.Array.mapWithIndex((index, item) =>
             <LineLink link=item id=index dispatch />
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
              value=url
              onChange={e => {
                let value = ReactEvent.Form.target(e)##value;
                setUrl(_ => value);
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
              onClick={_ => {dispatch(Create(name, url, description))}}>
              {React.string("Cadastrar")}
            </button>
          </td>
        </tr>
      </tbody>
    </table>
  </div>;
};