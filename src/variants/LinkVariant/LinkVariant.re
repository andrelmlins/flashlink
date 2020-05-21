type variant = {
  name: string,
  url: string,
  description: string,
};

let decodeJson = json =>
  Json.Decode.{
    name: json |> field("name", string),
    url: json |> field("url", string),
    description: json |> field("description", string),
  };

let decodeList = Json.Decode.array(decodeJson);