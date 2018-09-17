var util = require('util');
var dirMan = require('./modules/DirectoryManager');
var resMan = require('./modules/ResourceManager');
var classor = require('./modules/ClassCreator');

module.exports = {
    PostManager: function (arg) {
        var commands = arg.split(":"); 

        if (commands[0] == undefined || commands[1] == undefined) {
            console.log("commands: " + commands);        
            return;    
        }

        if (commands[0] == "GetDirs") { // GetDirs:../../res
            var flist;
            flist = dirMan.walkSync(commands[1]);

            /*console.log("------------------------------");
            console.log("flist: ");
            console.log(flist);*/

            return flist;
        } else if (commands[0] == "Tree") { // Tree:../../res
            //var fJSON = util.inspect(dirMan.TreeBuilder(commands[1]), false, null)
            var fJSON = dirMan.TreeBuilder(commands[1]);

            /*console.log("------------------------------");
            console.log("fJSON.name: ");
            console.log(fJSON.name);*/

            return fJSON;      
        } else if(commands[0] == "ReCore") { // ReCore:../../res
            var fJSON = dirMan.TreeBuilder(commands[1]);
            var CoreJSON = resMan.CoreRefresher(fJSON);
            resMan.WriteJSONFile(commands[1], CoreJSON);

            /*console.log("------------------------------");
            console.log("CoreJSON: ");
            console.log(CoreJSON);*/

            return CoreJSON;      
        } else if (commands[0] == "Classor") { // Classor:../../source/ -> engine/.. || game/.. ->className
            var clses = classor.FileCreator(commands[1]);

            return clses;
        } else {
            console.log("Command can't found!");
            return "Commmand can't found!";
        }

    }

};