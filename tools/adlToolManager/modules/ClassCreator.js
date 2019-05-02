const fs = require('fs');
const path = require('path');



FileCreator = function (classPath, options) {

    var className = path.basename(classPath);
    
    console.log("className: " + className);
    console.log("classPath: " + classPath);
    console.log("options: " + options);
    
    if (options != undefined) {
        settings = options.split(",");  
    }

    console.log("settings: " + settings);

    
    var cppFile = '#include "'+ className + '.h"\n\n'
                    // + ((settings[1] == 'true')?'#include "engine/adl_entities/adlEntity_factory.h"\n\n': '')
                    + className + '::' + className + '()\n'
                    + '{\n'
                    + ((settings[1] == 'true')?'\tREGISTER_COMPONENT(' + className + ')\n': '\n')
                    + '}\n\n'
                    // + className + '::~' + className + '()\n'
                    // + '{\n\n}\n\n'
                    + ((settings[0] == 'isComponent')?'bool ' + className + '::init(const rapidjson::Value& json_object) {\n\treturn true;\n}\n\n' : '')
                    + ((settings[0] == 'isComponent')?'void ' + className + '::post_init() {\n\n}\n\n' : '')
                    + ((settings[0] == 'isComponent')?'void ' + className + '::update(float dt) {\n\n}\n\n' : '')
                    + ((settings[0] == 'isComponent')?'void ' + className + '::destroy() {\n\n}\n\n' : '')
                    + ((settings[0] == 'isComponent')?'void ' + className + '::editor() {\n\tImGui::Indent();\n\n\tImGui::Unindent();\n}\n\n' : '')
    
    var hFile = '#ifndef ' + className + '_h__\n' // #include "adlEntity_component.h"
                + '#define ' + className + '_h__\n\n'
                + ((settings[2] != '')?'#include "engine/adl_entities/' + settings[2] + '.h"\n\n': '')
                + ((settings[3] != '')?'#include "game/GameGeneric/GameGenericTypedef.h"\n\n': '')
                + ((settings[2] != '')?'class ' + className + ' : public ' + settings[2] + ' { \n\n': 'class ' + className + ' { \n\n')
                + 'public:\n\n'
                + '\t' + className +'();\n\n'
                // + '\t~' + className + '();\n\n'
                + ((settings[0] == 'isComponent')?'\tvirtual bool init(const rapidjson::Value& json_object) override;\n' : '')
                + ((settings[0] == 'isComponent')?'\tvirtual void post_init() override;\n' : '')
                + ((settings[0] == 'isComponent')?'\tvirtual void update(float dt) override;\n' : '')
                + ((settings[0] == 'isComponent')?'\tvirtual void destroy() override;\n' : '')
                + ((settings[0] == 'isComponent')?'\tvirtual void editor() override;\n\n' : '')
                + 'private:\n\n'
                + '};\n\n'
                + '#endif //' + className + '_h__\n';

    fs.writeFileSync(classPath + '.cpp', cppFile);
    fs.writeFileSync(classPath + '.h', hFile);

    var clssFiles = {cpp: cppFile, h: hFile} 

    return clssFiles;
}

module.exports = {
    FileCreator: FileCreator
};