type variant = {
  name: string,
  link: string,
  description: string,
};

let decodeJson = json =>
  Json.Decode.{
    name: json |> field("name", string),
    link: json |> field("link", string),
    description: json |> field("description", string),
  };

let decodeList = Json.Decode.array(decodeJson);