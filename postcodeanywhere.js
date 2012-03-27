(function ($) {
  // Store our function as a property of Drupal.behaviors.
  Drupal.behaviors.postCodeAnywhere = {
    attach: function () {
    	  	
      // Only apply if postcodeanywhere wrapper is present.
      if ($(Drupal.settings.postcodeanywhere.id_wrapper)){
		    
    	  	// @todo Manage case where there is no country box selection (ie. UK only sites).
		    if(($(Drupal.settings.postcodeanywhere.id_country).val() == Drupal.settings.postcodeanywhere.id_country_uk_value) && (!$(Drupal.settings.postcodeanywhere.id_postcode).val())) {
		    			$(Drupal.settings.postcodeanywhere.id_company_wrapper).hide();
						$(Drupal.settings.postcodeanywhere.id_line1_wrapper).hide();
						$(Drupal.settings.postcodeanywhere.id_line2_wrapper).hide();
						$(Drupal.settings.postcodeanywhere.id_line3_wrapper).hide();
						$(Drupal.settings.postcodeanywhere.id_town_wrapper).hide();
						$(Drupal.settings.postcodeanywhere.id_county_wrapper).hide();
		  	}
		    
		    // create lookup button.
		    var postcodeanywhereLookupButton = '<input type="button" name="postcodeanywhere-lookup-button" id="postcodeanywhere-lookup-button" value="'+
		    									Drupal.t(Drupal.settings.postcodeanywhere.submit_label_value)+'">';
			  // create address list list on the fly.
				var postcodeanywhereAddressList = '<select style ="display:none" size = "10" name="postcodeanywhere-address-list" id="postcodeanywhere-address-list">';

				// append lookup button and address list to postcodeanywhere wrapper.
				$(postcodeanywhereLookupButton + '<br>' + postcodeanywhereAddressList).appendTo(Drupal.settings.postcodeanywhere.id_wrapper);

				// add onclick event to lookup button.
				$('#postcodeanywhere-lookup-button').click(function() {
				  if(!$(Drupal.settings.postcodeanywhere.id_postcode).val()) {
	   			  alert(Drupal.t('Please supply a complete valid Postcode'));
	          $(Drupal.settings.postcodeanywhere.id_postcode).focus();
	          return false;
				 	}
				 	else{
				 		$.getJSON(Drupal.settings.basePath+"postcodeanywhere/findbypostcode/"+$(Drupal.settings.postcodeanywhere.id_postcode).val(), function(data){
                var html = '';
                if(data != null){
                  if(data['error'] != null){
                    $(Drupal.settings.postcodeanywhere.id_company_wrapper).show();
          					$(Drupal.settings.postcodeanywhere.id_line1_wrapper).show();
          					$(Drupal.settings.postcodeanywhere.id_line2_wrapper).show();
          					$(Drupal.settings.postcodeanywhere.id_line3_wrapper).show();
          					$(Drupal.settings.postcodeanywhere.id_town_wrapper).show();
          					$(Drupal.settings.postcodeanywhere.id_county_wrapper).show();
          					alert(Drupal.t("Sorry there was an issue with the postcode lookup functionality, please enter address manually."));
          			// @todo This needs to allow the user to manually enter a postcode still.
                    $(Drupal.settings.postcodeanywhere.id_wrapper).hide()
                  }
                  else{
                    var len = data.length;
                    for (var i = 0; i< len; i++) {
                        html += '<option value="' + data[i].Id[0] + '">' + data[i].StreetAddress[0] + ', ' + data[i].Place[0] + '</option>';
                    }
                    $('#postcodeanywhere-address-list').html(html);
                    $('#postcodeanywhere-address-list').show();
                  }
                }
                else{
                   alert(Drupal.t("Sorry, no matching addresses found.\nPlease check Postcode"));
                }
            });
				 		return true;
				  }      
  			});
  			
			// add onchange event to address list.
			$('#postcodeanywhere-address-list').change(function() {

          $.getJSON(Drupal.settings.basePath+"postcodeanywhere/retrievebyid/"+$('#postcodeanywhere-address-list').val(), function(data){
        	  		// Set the Values
  					$(Drupal.settings.postcodeanywhere.id_company).val(data[0].Company[0]);
  					$(Drupal.settings.postcodeanywhere.id_line1).val(data[0].Line1[0]);
  					$(Drupal.settings.postcodeanywhere.id_line2).val(data[0].Line2[0]);
  					$(Drupal.settings.postcodeanywhere.id_line3).val(data[0].Line3[0]);
  					$(Drupal.settings.postcodeanywhere.id_town).val(data[0].PostTown[0]);
  					$(Drupal.settings.postcodeanywhere.id_county).val(data[0].County[0]);
  					$(Drupal.settings.postcodeanywhere.id_postcode).val(data[0].Postcode[0]);
          });	
				  
				// Show the Wrappers.
			  	$(Drupal.settings.postcodeanywhere.id_company_wrapper).show();
					$(Drupal.settings.postcodeanywhere.id_line1_wrapper).show();
					$(Drupal.settings.postcodeanywhere.id_line2_wrapper).show();
					$(Drupal.settings.postcodeanywhere.id_line3_wrapper).show();
					$(Drupal.settings.postcodeanywhere.id_town_wrapper).show();
					$(Drupal.settings.postcodeanywhere.id_county_wrapper).show();
					
					// Hide the list
					$('#postcodeanywhere-address-list').hide();
  			});
  			
  			// If we choose a non uk option hide postcode lookup.
  			$(Drupal.settings.postcodeanywhere.id_country).change(function() {
	  			if($(Drupal.settings.postcodeanywhere.id_country).val() == Drupal.settings.postcodeanywhere.id_country_uk_value){
	  				$(Drupal.settings.postcodeanywhere.id_wrapper).show();
	  			}
	  			else{
	  				$(Drupal.settings.postcodeanywhere.id_wrapper).hide();
						$(Drupal.settings.postcodeanywhere.id_company_wrapper).show();
						$(Drupal.settings.postcodeanywhere.id_line1_wrapper).show();
						$(Drupal.settings.postcodeanywhere.id_line2_wrapper).show();
						$(Drupal.settings.postcodeanywhere.id_line3_wrapper).show();
						$(Drupal.settings.postcodeanywhere.id_town_wrapper).show();
						$(Drupal.settings.postcodeanywhere.id_county_wrapper).show();
	  			}
	  		});
		  }
    }
  };
}(jQuery));
