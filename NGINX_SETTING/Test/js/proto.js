var temp_arg_name;
var temp_arg_type;
var temp_arg_size;
var temp_arg_subtype;

var prototypes_data = {

	"result" : {
		"type" : 0,
		"is_array" : true,
		"size" : 12
	},

	"args" : [
	]

}
 function removeItem(index){
    $.observable(prototypes_data.args).remove(index);
    $('select').material_select();
}
app = {
    selectedIndex: null,
    prototypes_data: prototypes_data,
    select: function(index) {
      if (this.selectedIndex !== index) {
        $.observable(this).setProperty("selectedIndex", index);
      }
    }
  };

function clone(obj) {
    if (null == obj || "object" != typeof obj) return obj;
    var copy = obj.constructor();
    for (var attr in obj) {
        if (obj.hasOwnProperty(attr)) copy[attr] = obj[attr];
    }
    return copy;
}

function sendTask() {
<<<<<<< c7aaf4c296052a2cd6cb4a42a86e6adf021b1ac2
	signature = JSON.parse(JSON.stringify(prototypes_data));
	var value = json.function .args;
=======
	signature = prototypes_data;
	var value = json.function.args;
>>>>>>> e2b6917dc5ba7424219c21104110f3a17a164e38
	//debugger;
	for (var i = 0; i < prototypes_data.args.length; i++) {
		value[i] = {
			"type" : prototypes_data.args[i].type,
			"arg_name" : prototypes_data.args[i].arg_name,
			"value" : []
		};

	}

	obj = {
		"signature" : signature,
		"json" : json
	}

	setTimeout(function() { $.templates.peopleTmpl.link("#list", obj, changeHandler); $('.collapsible').collapsible({
		accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
	}); }, 1000);
	
	console.log(JSON.stringify(json));

}

function protoInit() {
	$.templates({
		prototypeTmpl : "#prototypeTemplate"
	});


	$.templates.prototypeTmpl.link("#prototypes", prototypes_data);


  $("#removeArg").on("click",function() {
   
  });

	$("#addPrototype").on("click", function () {
		$.observable(prototypes_data.args).insert({
			"type" : parseInt($('#test_arg_type').val()),
			"arg_name" : "" + $('#test_arg_name').val(),
			"is_array" : $('#test_arg_subtype').val() === "Array",
			"size" : $('#test_arg_size').val()

		});
     $('select').material_select();
	});
}
