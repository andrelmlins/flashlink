const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const CopyPlugin = require("copy-webpack-plugin");

const PUBLIC_PATH = "./public";

module.exports = {
  entry: "./src/Index.bs.js",
  output: {
    path: path.resolve(__dirname, "build"),
    filename: "static/js/build.js",
    globalObject: "this"
  },
  mode: "production",
  plugins: [
    new CopyPlugin({ patterns: [{ from: "public", to: "." }] }),
    new HtmlWebpackPlugin({
      inject: true,
      template: `${PUBLIC_PATH}/index.html`
    })
  ]
};
