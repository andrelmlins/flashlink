type item = {
  name: string,
  link: string,
  description: string,
};

module Decode = {
  let option = json =>
    Json.Decode.{
      name: json |> field("name", string),
      link: json |> field("link", string),
      description: json |> field("description", string),
    };

  let all = Json.Decode.array(option);
};

type state = {list: array(item)};

type action =
  | Create(string, string, string)
  | ShowList;

let initialState = {list: [||]};

let reducer = (state, action) => {
  switch (action) {
  | Create(name, link, description) =>
    let newItem: item = {name, link, description};
    Js.Array.push(newItem, state.list);
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
      | Some(listStorage') => listStorage' |> Js_json.parseExn |> Decode.all
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
  Js.log(state.list);
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