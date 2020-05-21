type state = {list: array(LinkVariant.variant)};

type action =
  | Create(string, string, string)
  | Edit(int, string, string, string)
  | ShowList;

let initialState = {list: [||]};

let reducer = (state, action) => {
  switch (action) {
  | Create(name, url, description) =>
    let newItem: LinkVariant.variant = {name, url, description};
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
  | Edit(id, name, url, description) =>
    let newItem: LinkVariant.variant = {name, url, description};
    state.list[id] = newItem;
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