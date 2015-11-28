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

	"args" : [{
			"type" : 0,
			"arg_name" : "x",
			"is_array" : true,
			"size" : 12
		}, {
			"type" : 0,
			"arg_name" : "vasya",
			"is_array" : true,
			"size" : 12
		}
	]

}

function cloneObject(obj) {
	if (obj === null || typeof obj !== 'object') {
		return obj;
	}
}

function sendTask() {
	signature = prototypes_data;
	var value = json.function .args;
	//debugger;
	for (var i = 0; i < prototypes_data.args.length; i++) {
		value[i] = {
			"type" : prototypes_data.args[i].type,
			"arg_name" : prototypes_data.args[i].arg_name,
			"value" : [{
					"val" : [10, 12]
				}, {
					"val" : [14, 15]
				}
			]
		};

	}

	obj = {
		"signature" : signature,
		"json" : json
	}

	$.templates.peopleTmpl.link("#list", obj, changeHandler);
	setTimeout(function() { $('.collapsible').collapsible({
		accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
	}); }, 1000);
	
	console.log(JSON.stringify(json));

}

function protoInit() {
	$.templates({
		prototypeTmpl : "#prototypeTemplate"
	});

	$.templates.prototypeTmpl.link("#prototypes", prototypes_data);

	$("#addPrototype").on("click", function () {
		$.observable(prototypes_data.args).insert({
			"type" : $('#test_arg_type').val(),
			"arg_name" : "" + $('#test_arg_name').val(),
			"is_array" : $('#test_arg_subtype').val() === "Array",
			"size" : $('#test_arg_size').val()

		});
	});
}
