$.views.converters({
	intToStr : function (value) {
		return "" + value;
	},
	strToInt : function (value) {
		return parseInt(value);
	},
	setBit : function (value) {
		// "Convert Back": If checked, set this bit on the data,
		// or if unchecked, unset this bit on the data
		var mask = 1 << this.linkCtx.elem.getAttribute("data-bit"),
		// Shift first bit, 0, 1 or 2 bits to the left, to create a mask
		dataValue = this.tagCtx.args[0];
		// Take the current data value
		return value ? (dataValue | mask) : (dataValue & ~mask);
		// Use the mask to set or unset that bit on the data, and return the modified value
	},
	getBit : function (value) {
		// "Convert": Get the bit from the data, and check or uncheck the checkbox
		return (value >> this.linkCtx.elem.getAttribute("data-bit") & 1) === 1;
		// Shift 0, 1 or 2 bits to the right, and see if the first bit is set.
	},
	strToArr : function (value) {
		var res = value.split(",");
		if (res.length > 0)
			return new Array(new Array(res));
		else
			return new Array;
	},
	to : function (value) {
		return value;
	}
});

var signature = {
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

var json = {
	"operation" : "addtask",
	"etalon" : "hff",
	"name" : "test example",
	"lang" : "c++",
	"task" : 282,
	"function" : {
		"function_name" : "function",
		"type" : 0,
		"results" : [
		],
		"args" : [/*{
			"type" : 0,
			"arg_name" : "x",
			"value" : [{
			"val" : [10, 12]
			}, {
			"val" : [14, 15]
			}
			]
			}, {
			"type" : 0,
			"arg_name" : "vasya",
			"value" : [{
			"val" : [16, 12]
			}, {
			"val" : [13, 15]
			}
			]
			}*/
		]
	}
}

var obj = {
	"signature" : signature,
	"json" : json
}

$(document).ready(function () {
	$.templates({
		peopleTmpl : "#peopleTemplate"
	});
	protoInit();
	//$.templates.peopleTmpl.link("#list", obj, changeHandler);

	$("#add").on("click", function () {
		console.log("size" + json.function .args.length)
			for (var i = 0; i < json.function .args.length;
				i++) {
				$.observable(json.function .args[i].value).insert({
						"val" : 0
					});
			}
				$.observable(json.function .results).insert({
						"val" : 0
					});

					$('.collapsible').collapsible({
						accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
					});

	})

	$("#save").on("click", function () {

		console.log(JSON.stringify(json));
		$.ajax({
			type : 'post',
			url : 'http://ii.intita.com/',
			data : JSON.stringify(json),
			 contentType:"application/json; charset=utf-8",
			//crossDomain:true,
			//	response : 'json',
		//	dataType : 'text',
			error : function (xhr) {
				debugger;
				console.log(xhr.responseText);
			},
			success : function (data) {
				debugger;
				console.log("ФФФФФФФФФФФФФФФФФФФ" + data.responseText);
			}
		});
	})

	$.observable(obj).observeAll(changeHandler);

	$('.collapsible').collapsible({
		accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
	});
	$('select').material_select();

});

function changeHandler(ev, eventArgs) {

	//alert(obj.json.function.results);

}
