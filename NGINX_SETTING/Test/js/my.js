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
		"type" : 1,
		"is_array" : true,
		"size" : 12
	},

	"args" : [{
			"type" : 1,
			"arg_name" : "x",
			"is_array" : true,
			"size" : 12
		}, {
			"type" : 3,
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
	"task" : 279,
	"function" : {
		"function_name" : "function",
		"type" : 0,
		"results" : [{
				"val" : [10, 12]
			}, {
				"val" : [14, 15]
			}
		],
		"args" : [{
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
			}
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

	$.templates.peopleTmpl.link("#list", obj, changeHandler);

	$("#add").on("click", function () {

		console.log("size" + json.function .args.length)
			for (var i = 0; i < json.function .args.length;
				i++) {
				$.observable(json.function .args[i].value).insert({
						"val" : [10, 22]
					});
			}
				$.observable(json.function .results).insert({
						"val" : [10, 22]
					});

	})

	$("#save").on("click", function () {

	console.log(JSON.stringify(json));
		$.ajax({
			type : 'post',
			url : 'http://192.168.144.130/',
			data : JSON.stringify(json),
			//crossDomain:true,
		//	response : 'json',
			//dataType : 'jsonp',
			error : function (xhr, status, error) {
						for(var key in xhr.responseText){
        console.log(key);
   }
			},
			success : function (data) {
				alert(data);
			}
		});
	})

	$.observable(obj).observeAll(changeHandler);

	$('.collapsible').collapsible({
		accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
	});

});

function changeHandler(ev, eventArgs) {
	$('.collapsible').collapsible({
		accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
	});
	//alert(obj.json.function.results);

}
