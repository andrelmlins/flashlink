type state = {list: array(LinkVariant.variant)};

type action =
  | Create(string, string, string)
  | ShowList;

let initialState = {list: [||]};

let reducer = (state, action) => {
  switch (action) {
  | Create(name, link, description) =>
    let newItem: LinkVariant.variant = {name, link, description};
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

    {list: state.list};
  | ShowList =>
    let listStorage =
      Dom_storage.getItem("@flashlink:list", Dom_storage.localStorage);

    let result =
      switch (listStorage) {
      | Some(listStorage') =>
        listStorage' |> Js_json.parseExn |> LinkVariant.decodeList
      | None => [||]
      };

    {list: result};
  };
};