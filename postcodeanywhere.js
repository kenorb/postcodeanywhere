// FOLLOWED VARIABLES SHOULD BE CHANGE DEPENDS OF YOUR FORM 
// TODO: later should be moved into settings page
var pca_account_code = 'account_code'; /* CHANGE THIS */
var pca_licence = 'n***-**3*-p*8*-g*9*'; /* CHANGE THIS INTO YOUR LICENCE CODE */
var pca_id_postcode = 'edit-field-address-postcode-0-value'; // TYPE HERE YOUR ID OF POSTCODE FIELD
var pca_id_postcode_wrapper = 'edit-field-address-postcode-0-value-wrapper'; // TYPE HERE YOUR ID OF POSTCODE WRAPPER
var pca_id_house_number = 'edit-field-company-house-name-number-0-value';  // TYPE HERE YOUR ID OF HOUSE_NUMBER FIELD
var pca_id_property_name = '';  // TYPE HERE YOUR ID OF PROPERTY_NAME FIELD
var pca_id_street = 'edit-field-company-street-address-0-value';  // TYPE HERE YOUR ID OF STREET_NAME FIELD
var pca_id_city = 'edit-field-company-address-town-0-value';  // TYPE HERE YOUR ID OF CITY FIELD
var pca_id_county = 'edit-field-company-address-county-0-value';  // TYPE HERE YOUR ID OF COUNTY FIELD
var pca_id_country = '';  // TYPE HERE YOUR ID OF COUNTRY FIELD (NOT NECESSARY)
var pca_id_uk_value = '226';  // TYPE HERE YOUR VALUE OF COUNTRY WHICH IS UK (other choices will show error) (NOT NECESSARY)

var pca_showAlert = 1; // SHOW PCA ERRORS
var pca_url = 'http://services.postcodeanywhere.co.uk/inline.aspx?'; // USUALLY YOU DON'T NEED TO CHANGE THAT

if (Drupal.jsEnabled) {
  // When the DOM is ready, try an AJAX content load
  
  $(document).ready(function() {
    pcaAfterLoad();
  }
  );
}

function pcaAfterLoad() {
// author: kenorb@gmail.com (27/10/2008)

    // init variables
    postcode_wrapper = document.getElementById(pca_id_postcode_wrapper); // get element
    house_number = document.getElementById(pca_id_house_number); // get element
    property_name = document.getElementById(pca_id_property_name); // get element
    if (postcode_wrapper == null) {
        return; // if wrapped doesn't exist, RETURN the function (please check the proper configuration)
    }

    // create Find Postcode button on the fly
    var pca_button = document.createElement('input');
    pca_button.type = 'button';
    pca_button.name = 'FindPostcode';
    pca_button.id = 'FindPostcode';
    pca_button.value = 'Find Postcode';
    pca_button.onclick = function() { PostcodeFinder() }; // IE compability syntax
    postcode_wrapper.appendChild(pca_button);
    // add br tag after button on the fly
    var pca_br = document.createElement('br');
    postcode_wrapper.appendChild(pca_br);
    // create objAddressFinder list on the fly
    var pca_list = document.createElement('select');
    pca_list.name = 'objAddressFinder';
    pca_list.id = 'objAddressFinder';
    pca_list.width = '100%';
    pca_list.size = '10';
    pca_list.onchange = function() { FetchAddress(this.options[this.selectedIndex].value) }; // IE compability syntax
    pca_list.setAttribute('style','display:none');
    pca_list.style.cssText = 'display:none'; // IE issue fix
    postcode_wrapper.appendChild(pca_list);
    //postcode_wrapper.setAttribute('align','center'); // center the postcode wrapper // ENABLE IT IF NECESSARY
}

function pcaByPostcodeFilteredBegins(building, postcode, account_code, license_code, machine_id, bname) {
    if (!building) {
	building = bname;
    }
	
    var scriptTag = document.getElementById("pcaScript");
    var headTag = document.getElementsByTagName("head").item(0);
    var strUrl = "";

    //Build the url
    strUrl = pca_url;
    strUrl += "&action=lookup";
    strUrl += "&type=by_postcode";
    strUrl += "&building=" + escape(building.value);
    strUrl += "&postcode=" + escape(postcode.value);
    strUrl += "&account_code=" + escape(account_code);
    strUrl += "&license_code=" + escape(license_code);
    strUrl += "&machine_id=" + escape(machine_id);
    strUrl += "&callback=pcaByPostcodeFilteredEnd";

    //Make the request
    if (scriptTag) {
	try {
	    headTag.removeChild(scriptTag);
	}
    catch (e) {
	//Ignore
	}
    }
    scriptTag = document.createElement("script");
    scriptTag.src = strUrl
    scriptTag.type = "text/javascript";
    scriptTag.id = "pcaScript";
    headTag.appendChild(scriptTag);
}

function pcaByPostcodeFilteredEnd() {
    //Test for an error
    if (pcaIsError) {
	msgArr = pcaErrorMessage.split(' ');
	pca_showAlert = 1;
	for(i=0; i < msgArr.length; i++) {
	    if(msgArr[i] == 'credit')
	    showAlert=0;
	}
	if(pca_showAlert == 1) {
	    alert(pcaErrorMessage);
	} else {
	    alert("Sorry, there was an unknown error. Please enter the address manually\nor try again later.");
	}
    } else {
	//Check if there were any items found
	if (pcaRecordCount == 0) {
	    alert("Sorry, no matching address found.\nPlease check House Number/Property Name or leave empty");
	} else if (pcaRecordCount == 1) {
	    FetchAddress(pca_id[0]);
	    void(0);//return true;  
	} else if (pcaRecordCount > 1) {
	    //Populate the select list
	    selBox = document.getElementById("objAddressFinder")
	    selBox.length=pcaRecordCount;
	    for (intCounter=0; intCounter < pcaRecordCount; intCounter++) {
		selBox.options[intCounter].text = pca_description[intCounter];
		selBox.options[intCounter].value = pca_id[intCounter];
		selBox.options[intCounter].title = pca_description[intCounter];
	    }
	    selBox.disabled=false;
	    selBox.style.display = "block";
	}
    }
}

function PostcodeFinder() {
    postcode = document.getElementById(pca_id_postcode); // get element
    house_number = document.getElementById(pca_id_house_number); // get element
    property_name = document.getElementById(pca_id_property_name); // get element
    country = document.getElementById(pca_id_country);
    postcode = document.getElementById(pca_id_postcode); // get element

    if ((pca_id_uk_value == "" || pca_id_country == "") || (country && country.value == pca_id_uk_value)) {
	if(postcode=='') {
	    alert('Please supply a complete valid Postcode');
	    postcode.focus();
	    return false;
	} else {
	    pcaByPostcodeFilteredBegins(house_number, postcode,  pca_account_code, pca_licence, '', property_name);
	    return true;
	}
    } else if (country && pca_id_uk_value != '') {
	if(confirm('Country you select is not UK!! Click "OK" to change to UK')){
	    country.value = pca_id_uk_value;
	    if(postcode=='') {
		alert('Please supply a complete valid Postcode');
		postcode.focus();
		return false;
	    } else {
		pcaByPostcodeFilteredBegins(house_number.value, postcode.value,  pca_account_code, pca_licence, '', property_name);
		return true;
	    }
	} else {
	    postcode.focus();
	    return false;
	}
    }
}

function pcaFetchAddressBegin(id, language, style, account_code, license_code, machine_id, options) {
      var scriptTag = document.getElementById("pcaScript");
      var headTag = document.getElementsByTagName("head").item(0);
      var strUrl = "";

      //Build the url
      strUrl = "http://services.postcodeanywhere.co.uk/inline.aspx?";
      strUrl += "&action=fetch";
      strUrl += "&id=" + escape(id);
      strUrl += "&language=" + escape(language);
      strUrl += "&style=" + escape(style);
      strUrl += "&account_code=" + escape(account_code);
      strUrl += "&license_code=" + escape(license_code);
      strUrl += "&machine_id=" + escape(machine_id);
      strUrl += "&options=" + escape(options);
      strUrl += "&callback=pcaFetchAddressEnd";

      //Make the request
      if (scriptTag) {
	   try {
	         headTag.removeChild(scriptTag);
	     }
	   catch (e) {
	         //Ignore
	     }
	}
      scriptTag = document.createElement("script");
      scriptTag.src = strUrl
      scriptTag.type = "text/javascript";
      scriptTag.id = "pcaScript";
      headTag.appendChild(scriptTag);
   }

function FetchAddress(aid) {
    pcaFetchAddressBegin(aid,'english','raw', pca_account_code, pca_licence, '', '');
    return true;
}


var formFields=new Array()  ;

function Fields(fieldsArray){
    var arg=Fields.arguments;
    var len=arg.length;
    for (var i = 0; i < len; i++) {
	formFields[i]=arg[i];
    }
}

function pcaFetchAddressEnd() {
    if (pcaIsError) {
	//Handle no funds error message
	msgArr = pcaErrorMessage.split(' ');

	showAlert = 1;
	for(i=0; i < msgArr.length; i++) {
	    if(msgArr[i] == 'funds')
	    showAlert=0;
	}
	if(showAlert==1) {
	    alert(pcaErrorMessage);
	} else {
	    alert("Sorry, there was an unknown error. Please enter the address manually\nor try again later.");
	}
    } else {
	if (pcaRecordCount==0) {
	    alert("Sorry, no matching items found.\nPlease check House Number/Property Name");
	} else {
	    var pnumber=typeof pca_reformatted_building_number != "undefined" ? pca_reformatted_building_number[0] : '';
	    var pname = '';
	    if (typeof pca_building_name != "undefined") {
		pname = pca_building_name[0];
	    } else if (typeof pca_reformatted_sub_building != "undefined") {
		pname = pca_reformatted_sub_building[0]+', ' + pname;
	    } else if (typeof pca_organisation_name != "undefined") {
		pname = pca_organisation_name[0]+', ' + pname;
	    }
	    var street = '';
	    if (typeof pca_thoroughfare_name != "undefined" || typeof pca_thoroughfare_descriptor != "undefined") {
		street = pca_thoroughfare_name[0] +' '+ pca_thoroughfare_descriptor[0];
	    }
	    if (typeof pca_dependent_locality != "undefined") {
		street += ','+pca_dependent_locality[0];
	    }

	    var el=document.getElementById(pca_id_house_number);
	    if(el) el.value=pnumber;

	    var el=document.getElementById(pca_id_property_name);
	    if(el) el.value=pname;

	    var el=document.getElementById(pca_id_street);
	    if(el) el.value=street;

	    var el=document.getElementById(pca_id_city);
	    if(el) el.value=pca_post_town[0];

	    var el=document.getElementById(pca_id_county);
	    if(el) el.value=pca_county[0];

	    var el=document.getElementById(pca_id_postcode);
	    if(el) el.value=pca_postcode[0];

	    document.getElementById("objAddressFinder").style.display = "none";
	}
    }
}

