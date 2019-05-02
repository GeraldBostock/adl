const fs = require('fs');
const path = require('path');


CoreRefresher = function (dirFile, coreFile = {}) {
    
    // console.log("Dir Files: ");
    // console.log(dirFile);
    // console.log("Core Files: ");
    // console.log(coreFile);

    // console.log("Dir File Name: ");
    // console.log(dirFile.name);


    for (const item in dirFile) {
        if (dirFile.hasOwnProperty(item)) {
            const element = dirFile[item];
            
            if (dirFile.name == "fonts" ||
              dirFile.name == "models" ||
               dirFile.name == "textures" ||
               dirFile.name == "scenes" ||
               dirFile.name == "terrains" ||
               dirFile.name == "entities") {
                var propertyName = dirFile.name;
                var propertyData = element;

                if(typeof(element) === 'object') {
                    propertyData = PropertyWalker(element, propertyName, dirFile.name);
                    //console.log(propertyData);
                }

                coreFile[propertyName] = propertyData;
                
            } else if(typeof(element) === 'object') {
                CoreRefresher(element, coreFile);
            }
        }
    }
    return coreFile;
}

PropertyWalker = function (data, propertyName, baseDirectory) {
    
    if (Array.isArray(data)) {// Folder Array
        var newData = [];
        for (let item = 0; item < data.length; item++) {
            if (data.hasOwnProperty(item)) {
                var element = data[item];
                // console.log("Folder Array: ");
                // console.log(element);

                var n = PropertyWalker(element, propertyName, baseDirectory);
                
                if (n != undefined) {
                    newData.push(n);                     
                }
            }        
        }

        data = newData;
        data = Array.prototype.concat.apply([], data); // Nested JSON To Flatten JSON

    } else if(data.children !== undefined){ // Folder
        // console.log("Folder: ");
        // console.log(data);

        var n = PropertyWalker(data.children, propertyName, baseDirectory);

        if (n != undefined) {
           data = n;
        }  
    } else { // File
        // console.log("File: ");
        // console.log(data);
        data = PropertyParser(data, baseDirectory);
    }


    return data;
}

PropertyParser = function (data, baseDirectory) { // Edit for different needs
    // console.log("\t\t\t BaseDir:" + baseDirectory);

    if (baseDirectory === "fonts") { // fonts // path.extname(data.name) === ".tff"
        data.name = path.basename(data.name, path.extname(data.name));
        //console.log(path.basename(data.name, path.extname(data.name).toString()));
    } else if (baseDirectory === "models") {
        //console.log("\n\n\t\t" + path.extname(data.path));
        
        if (path.extname(data.path) === ".obj" || path.extname(data.path) === ".fbx" || path.extname(data.path) === ".dae") {
            data.name = path.basename(data.name, path.extname(data.name));                    
        } else {
            data = undefined;
        }
    } else if (baseDirectory === "textures") {
        data.specular_map_path = data.path.replace(/\.[^/.]+$/g, "") + "_Specular" + path.extname(data.path);        
    } else if (baseDirectory === "terrains") {
        // console.log(path.basename(data.name, path.extname(data.name)));
        data.height_map = data.path;
        data.path = undefined;
    } else if (baseDirectory === "entities") {
        // console.log(path.basename(data.name, path.extname(data.name)));
        data.name = path.basename(data.name, path.extname(data.name));
    } else {
        //data.name = path.basename(data.name, path.extname(data.name));
        console.log(path.basename(data.name, path.extname(data.name)));
    }
    return data;
}

WriteJSONFile = function (pathName, content = {}) {
    /*console.log("¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨");
    console.log(content);*/
    
    var others = JSON.parse(fs.readFileSync(pathName + "/shaders.json", 'utf8'));
    content.shaders = others.shaders;
    content.cube_maps = others.cube_maps;

    data = JSON.stringify(content, RootReplacer, 2);

    /*console.log("con:");
    console.log(JSON.stringify(content, RootReplacer, 2));*/

    fs.writeFileSync(pathName + "/core.json", data);
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

module.exports = {
    CoreRefresher: CoreRefresher,
    WriteJSONFile: WriteJSONFile
};