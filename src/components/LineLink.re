[@react.component]
let make = (~link: LinkVariant.variant, ~id: int, ~dispatch) => {
  let (edit, setEdit) = React.useState(() => false);
  let (name, setName) = React.useState(() => link.name);
  let (url, setUrl) = React.useState(() => link.url);
  let (description, setDescription) = React.useState(() => link.description);

  <tr>
    <td>
      {edit
         ? <input
             className="form-control form-control-sm"
             autoFocus=true
             value=name
             onChange={e => {
               let value = ReactEvent.Form.target(e)##value;
               setName(_ => value);
             }}
           />
         : React.string(link.name)}
    </td>
    <td>
      {edit
         ? <input
             className="form-control form-control-sm"
             value=url
             onChange={e => {
               let value = ReactEvent.Form.target(e)##value;
               setUrl(_ => value);
             }}
           />
         : React.string(link.url)}
    </td>
    <td>
      {edit
         ? <input
             className="form-control form-control-sm"
             value=description
             onChange={e => {
               let value = ReactEvent.Form.target(e)##value;
               setDescription(_ => value);
             }}
           />
         : React.string(link.description)}
    </td>
    <td>
      {!edit
         ? <>
             <button
               className="btn btn-info btn-sm"
               onClick={_ => setEdit(_ => true)}
               ariaLabel="Edit">
               <i className="fa fa-edit" />
             </button>
             <button
               className="btn btn-danger btn-sm"
               onClick={_ => {dispatch(LinkReducer.Delete(id))}}
               ariaLabel="Delete">
               <i className="far fa-trash-alt" />
             </button>
           </>
         : <>
             <button
               className="btn btn-success btn-sm"
               onClick={_ => {
                 dispatch(LinkReducer.Edit(id, name, url, description));
                 setEdit(_ => false);
               }}>
               <i className="fas fa-check" />
             </button>
             <button
               className="btn btn-secondary btn-sm"
               onClick={_ => setEdit(_ => false)}
               ariaLabel="Cancel">
               <i className="fa fa-backspace" />
             </button>
           </>}
    </td>
  </tr>;
};