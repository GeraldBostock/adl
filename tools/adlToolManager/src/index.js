// index

// Post requests
function SendData(command) {
    var request = new XMLHttpRequest();
    request.open('POST', '/', true);
    request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
    request.onload = function() {
        if (request.status >= 200 && request.status < 400) {
            Manager(this.responseText);
        }
    };

    request.send(command);
}    

function SendCommandData() {
    var request = new XMLHttpRequest();
    request.open('POST', '/', true);
    request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
    request.onload = function() {
        if (request.status >= 200 && request.status < 400) {
            Manager(this.responseText);
        }
    };
    var command = document.getElementById("command").value;

    request.send(command);
}

// Get request
function GetFile() {
    var request = new XMLHttpRequest();
    request.open('GET', '/', true);

    request.onload = function() {
    if (request.status >= 200 && request.status < 400) {
        document.getElementById("res").innerHTML = this.responseText;
    }
    };
    request.send();
}

// Replacer
function RootReplacer(key, value) {
    if (typeof(value) == "string") { // key == "path"
        value = value.replace(/\\/g, "/"); // Win "\" to "/" 
        value = value.replace(/..\/..\//g, ""); // Root to res file
    }
    if (key  == "name") {  
        value = value.replace(/\.[^/.]+$/g, "");
    }

    return value;
}

// Display functions
function TabManager(ManagerId) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("TabContent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("TabLink");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(ManagerId).style.display = "block";
}

// Classor
function Classor() {
    var options = 
        document.getElementById('ClassFormat').value + "," // settings[0]
        + document.getElementById('ClassRegister').checked + "," // settings[1]
        + document.getElementById('ClassParent').value; // settings[2]
        + document.getElementById('GameGeneric').checked + "," // settings[3]
    
    var cPath = document.getElementById("pathGame").checked?'game/':'engine/';
    console.log(cPath);


    var commands = 'Classor:../../source/' + cPath + document.getElementById('ClassName').value + ':' + options
    console.log(commands);
    
    SendData(commands);
}

//Display
function ClassOptionsController() {
    var cFormat = document.getElementById('ClassFormat');
    if(cFormat.value == 'isCpp'){
        document.getElementById('ClassOptions').hidden = true;
        document.getElementById('ClassRegister').checked = false;
        document.getElementById('GameGeneric').checked = false;
        document.getElementById('ClassParent').value = "";            
    }else{
        document.getElementById('ClassOptions').hidden = false;
        document.getElementById('ClassRegister').checked = true;
        document.getElementById('GameGeneric').checked = true;
    }
}

// Data Table
var tabledata = [{name: "FirstName",age:18, progress:80}, {name: "SecondName"}]

var table = new Tabulator("#example-table", {
    data:tabledata, 
    layout:"fitDataFill",
    tooltips:true,  
    addRowPos:"top",          //when adding a new row, add it to the top of the table
    history:true,             //allow undo and redo actions on the table
    pagination:"local",       //paginate the data
    paginationSize:7,         //allow 7 rows per page of data
    movableColumns:true,      //allow column order to be changed
    resizableRows:true,       //allow row order to be changed
    initialSort:[             //set the initial sort order of the data
        {column:"name", dir:"asc"},
    ],
    columns:[                 //define the table columns
        {title:"Name", field:"name", width:90, editor:"input"},
        {title:"Task Progress", field:"progress", width:130, align:"left", formatter:"progress", editor:true},
        {title:"Gender", field:"gender", width:95, editor:"select", editorParams:{values:["Male", "Female"]}},
        {title:"Age", field:"age", width:80, sorter:"number", align:"center", editor:true},
        {title:"Happy", field:"happy", formatter:"star", align:"center", width:100, editor:true},
        // {title:"Color", field:"col", width:130, editor:"input"},
        // {title:"Date Of Birth", field:"dob", width:130, sorter:"date", align:"center"},
        // {title:"Driver", field:"car", width:90,  align:"center", formatter:"tickCross", sorter:"boolean", editor:true},
    ],
});