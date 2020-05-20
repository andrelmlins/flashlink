type item = {
  name: string,
  link: string,
  description: string,
};

type state = {
  list: array(item),
  count: int,
};

type action =
  | Create(string, string, string)
  | ShowList;

let initialState = {list: [||], count: 0};

let reducer = (state, action) => {
  switch (action) {
  | Create(name, link, description) =>
    let newItem: item = {name, link, description};
    let a = Js.Array.push(newItem, state.list);
    let listString = Js_json.stringifyAny(state.list);

    switch (listString) {
    | Some(listString') =>
      Dom_storage.setItem(
        "@flashlink:list",
        listString',
        Dom_storage.localStorage,
      )
    | None => ()
    };

    state;
  | ShowList =>
    let listStorage =
      Dom_storage.getItem("@flashlink:list", Dom_storage.localStorage);

    let result =
      switch (listStorage) {
      |> Some(listStorage') =>
        Js_json.decodeArray(Js_json.parseExn(listStorage'))
      | None => [||]
      };

    {list: result};
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
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