(function ($) {
  // Store our function as a property of Drupal.behaviors.
  Drupal.behaviors.postCodeAnywhere = {
    attach: function () {

      // Only apply if postcodeanywhere wrapper is present.
      if ($(Drupal.settings.postcodeanywhere.id_wrapper)) {

          // @todo Manage case where there is no country box selection (ie. UK only sites).
        if (($(Drupal.settings.postcodeanywhere.id_country).val() == Drupal.settings.postcodeanywhere.id_country_uk_value) && (!$(Drupal.settings.postcodeanywhere.id_postcode).val())) {
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
        var postcodeanywhereAddressList = '<div style="display:none;" size="10" name="postcodeanywhere-address-list" id="postcodeanywhere-address-list">';
        // Create spinner container
        var postcodeanywhereloader = '<div id="postcodeloading" class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div><div class="message">Please wait...</div></div>';

        // append lookup button and address list to postcodeanywhere wrapper.
        $(postcodeanywhereLookupButton).insertAfter(Drupal.settings.postcodeanywhere.id_postcode);
        $(postcodeanywhereloader).insertAfter(Drupal.settings.postcodeanywhere.id_postcode);
        $(postcodeanywhereAddressList).appendTo(Drupal.settings.postcodeanywhere.id_wrapper);

        // Add loading spinner div to end of postcode anywhere.
        $('#postcodeloading')
            .hide()  // hide it initially
            .ajaxStart(function() {
                $(this).show();
            })
            .ajaxStop(function() {
                $(this).hide();
            });

        // add onclick event to lookup button.
        $(Drupal.settings.postcodeanywhere.id_lookup_button).click(function() {
          if (!$(Drupal.settings.postcodeanywhere.id_postcode).val()) {
             alert(Drupal.t('Please supply a complete valid Postcode'));
            $(Drupal.settings.postcodeanywhere.id_postcode).focus();
            return false;
           }
           else {
             $.getJSON(Drupal.settings.basePath+"pca/findbypostcode/"+$(Drupal.settings.postcodeanywhere.id_postcode).val(), function(data){
                var html = '';
                if (data != null) {
                  if (data['error'] != null) {
                    $(Drupal.settings.postcodeanywhere.id_company_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_line1_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_line2_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_line3_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_town_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_county_wrapper).show();
                    alert(Drupal.t("Sorry there was an issue with the postcode lookup functionality, please enter address manually."));
                  }
                  else {
                    var len = data.length;
                    for (var i = 0; i< len; i++) {
                        html += '<input type="radio" value="' + data[i].Id + '" id="' + data[i].Id + '" name="postcodeanywhere-address" /><label for="' + data[i].Id +'">' + data[i].StreetAddress + ', ' + data[i].Place + '</label>';
                    }
                    $('#postcodeanywhere-address-list').html(html);
                    // $('#postcodeanywhere-address-list').slideDown();
                    $('#postcodeanywhere-address-list').show('slow');

                    // add onchange event to address list.
                    $('input[name="postcodeanywhere-address"]').change(function() {
                      $.getJSON(Drupal.settings.basePath+"pca/retrievebyid/"+$(this).val(), function(data){
                        // Set the Values
                        // If the results are strings
                        if (typeof data[0].Company == 'string') {
                          $(Drupal.settings.postcodeanywhere.id_company).val(data[0].Company).change();
                          $(Drupal.settings.postcodeanywhere.id_line1).val(data[0].Line1).change();
                          $(Drupal.settings.postcodeanywhere.id_line2).val(data[0].Line2).change();
                          $(Drupal.settings.postcodeanywhere.id_line3).val(data[0].Line3).change();
                          $(Drupal.settings.postcodeanywhere.id_town).val(data[0].PostTown).change();
                          $(Drupal.settings.postcodeanywhere.id_county).val(data[0].County).change();
                          $(Drupal.settings.postcodeanywhere.id_postcode).val(data[0].Postcode).change();
                        }
                        // If the results are objects
                        if (typeof data[0].Company == 'object') {
                          $(Drupal.settings.postcodeanywhere.id_company).val(data[0].Company[0]).change();
                          $(Drupal.settings.postcodeanywhere.id_line1).val(data[0].Line1[0]).change();
                          $(Drupal.settings.postcodeanywhere.id_line2).val(data[0].Line2[0]).change();
                          $(Drupal.settings.postcodeanywhere.id_line3).val(data[0].Line3[0]).change();
                          $(Drupal.settings.postcodeanywhere.id_town).val(data[0].PostTown[0]).change();
                          $(Drupal.settings.postcodeanywhere.id_county).val(data[0].County[0]).change();
                          $(Drupal.settings.postcodeanywhere.id_postcode).val(data[0].Postcode[0]).change();
                        }
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
                  }
                }
                else {
                   alert(Drupal.t("Sorry, no matching addresses found.\nPlease check Postcode"));
                }
            });
             return true;
          }
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

