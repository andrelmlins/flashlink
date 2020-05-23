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

  <>
    <nav
      className="navbar"
      style={ReactDOMRe.Style.make(
        ~backgroundColor="#455a64",
        ~marginBottom="20px",
        (),
      )}>
      <div className="container">
        <span className="navbar-brand">
          <img
            src="/flash.gif"
            style={ReactDOMRe.Style.make(
              ~width="40px",
              ~marginRight="15px",
              (),
            )}
          />
          {React.string("FlashLink")}
        </span>
      </div>
    </nav>
    <div className="container">
      <div className="table-responsive">
        <table className="table">
          <thead className="thead-light">
            <tr>
              <th> {React.string("Name")} </th>
              <th> {React.string("Link")} </th>
              <th> {React.string("Description")} </th>
              <th> {React.string("#")} </th>
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
                  className="form-control form-control-sm"
                  placeholder="Name"
                  onChange={e => {
                    let value = ReactEvent.Form.target(e)##value;
                    setName(_ => value);
                  }}
                />
              </td>
              <td>
                <input
                  value=url
                  className="form-control form-control-sm"
                  placeholder="Link"
                  onChange={e => {
                    let value = ReactEvent.Form.target(e)##value;
                    setUrl(_ => value);
                  }}
                />
              </td>
              <td>
                <input
                  value=description
                  className="form-control form-control-sm"
                  placeholder="Description"
                  onChange={e => {
                    let value = ReactEvent.Form.target(e)##value;
                    setDescription(_ => value);
                  }}
                />
              </td>
              <td>
                <button
                  className="btn btn-primary btn-sm"
                  onClick={_ => {dispatch(Create(name, url, description))}}>
                  {React.string("Cadastrar")}
                </button>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>
  </>;
};