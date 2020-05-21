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
             <button onClick={_ => setEdit(_ => true)}>
               {React.string("Editar")}
             </button>
             <button onClick={_ => {dispatch(LinkReducer.Delete(id))}}>
               {React.string("Deletar")}
             </button>
           </>
         : <>
             <button
               onClick={_ => {
                 dispatch(LinkReducer.Edit(id, name, url, description));
                 setEdit(_ => false);
               }}>
               {React.string("Salvar")}
             </button>
             <button onClick={_ => setEdit(_ => false)}>
               {React.string("Cancelar")}
             </button>
           </>}
    </td>
  </tr>;
};