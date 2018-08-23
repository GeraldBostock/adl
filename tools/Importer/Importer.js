var fs = require('fs');

var core;

if (process.argv.length <= 2) {
  console.log(process.argv);
  console.log('Arg problem');
  process.exit(-1);
}

console.log('Args:');
console.log(process.argv);



if (process.argv[2] == 'models') {

  var argName = process.argv[3];
  var argPath = process.argv[4];

  fs.readFile('../../res/core.json', function(err, data){
    if(err) throw err;
    console.log(data.toString());
    core = JSON.parse(data);
    core.models.push({ name: argName, path: "res/models/" + argPath });
    console.log(core.models);
    data.models = core.models;

    console.log();

    fs.writeFile('../../res/core.json', JSON.stringify(core, null, 2), function (e) {
      console.log(e);
      console.log("File Updated!");
    });

  });

} else if (process.argv[2] == 'shaders') {

  var argName = process.argv[3];
  var argPath1 = process.argv[4];
  var argPath2 = process.argv[5];

  fs.readFile('../../res/core.json', function(err, data){
    if(err) throw err;
    console.log(data.toString());
    core = JSON.parse(data);
    core.shaders.push({name: argName, vertex_shader_path: "res/shaders/" + argPath1, fragment_shader_path: "res/shaders/" + argPath2});
    console.log(core.models);
    data.shaders = core.shaders;
  });

} else if (process.argv[2] == 'fonts') {

  var argName = process.argv[3];
  var argPath = process.argv[4];

  fs.readFile('../../res/core.json', function(err, data){
    if(err) throw err;
    console.log(data.toString());
    core = JSON.parse(data);
    core.fonts.push({ name: argName, path: "res/fonts/" + argPath });
    console.log(core.fonts);
    data.fonts = core.fonts;
  });

} else {
  console.log("Missing type!");
  console.log("All Types: models, shaders, fonts");
}
