const fs = require('fs');
const path = require('path');


CoreRefresher = function (dirFile, coreFile = {}) {
    
    /*console.log("Dir Files: ");
    console.log(dirFile);
    console.log("Core Files: ");
    console.log(coreFile);

    console.log("Dir File Name: ");
    console.log(dirFile.name);*/


    for (const item in dirFile) {
        if (dirFile.hasOwnProperty(item)) {
            const element = dirFile[item];
            
            if (dirFile.name == "fonts" || dirFile.name == "models" || dirFile.name == "textures") {
                var propertyName = dirFile.name;
                var propertyData = element;

                if(typeof(element) === 'object') {
                    propertyData = PropertySyntaxer(element, propertyName);
                }

                coreFile[propertyName] = propertyData;
                
            } else if(typeof(element) === 'object') {
                CoreRefresher(element, coreFile);
            }
        }
    }
    return coreFile;
}

PropertySyntaxer = function (data, propertyName) { // Specified for Models sub folder and textures
    for (var item = 0; item < data.length; item++) {
        
        if (data.hasOwnProperty(item)) {
            if (data[item].children != undefined) {
                data[item].path = undefined;
                data[item].path = data[item].children[1].path;
                data[item].children = undefined; 
            }

            if (propertyName == "textures") {
                data[item].specular_map_path = data[item].path.replace(/\.[^/.]+$/g, "") + "_specular" + path.extname(data[item].path);

                if (data[item].name.includes("_specular")) {
                    data.splice(item, 1);
                    item-=1;
                }
            }
        }   
    }
    return data;
}

WriteJSONFile = function (pathName, content = {}) {
    /*console.log("¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨");
    console.log(content);*/
    
    var shaders = JSON.parse(fs.readFileSync(pathName + "/shaders.json", 'utf8'));
    content.shaders = shaders.shaders;

    data = JSON.stringify(content, RootReplacer, 2);

    /*console.log("con:");
    console.log(JSON.stringify(content, RootReplacer, 2));*/

    fs.writeFileSync(pathName + "/CoreSample.json", data);
}

function RootReplacer(key, value) {
    if (typeof(value) == "string") { // key == "path"
        value = value.replace(/\\/g, "/"); // Win "\" to "/" 
        value = value.replace(/..\/..\//g, ""); // Root to res file
    }
    if (key  == "name") {  
        value = value.replace(/\.[^/.]+$/g, ""); // Remove ext 
    }

    return value;
}

/*
TreeBuilder = function (filename) {
    var stats = fs.lstatSync(filename),
        info = {
            name: path.basename(filename),
            path: filename
        };

    if (stats.isDirectory()) {
        info.type = "folder";
        info.children = fs.readdirSync(filename).map(function(child) {
            return TreeBuilder(filename + '/' + child);
        });
    } else {
        info.type = "file";
    }

    return info;
}*/



module.exports = {
    CoreRefresher: CoreRefresher,
    WriteJSONFile: WriteJSONFile
};