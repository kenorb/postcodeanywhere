/**
 * @file
 */
(function ($) {
  // Store our function as a property of Drupal.behaviors.
  Drupal.behaviors.postCodeAnywhere = {
    attach: function () {

      // Only apply if PCA wrapper is present.
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

        if ($(Drupal.settings.postcodeanywhere.addressfield)) {
          var postcodeanywhereLookupButton = '';
          var postcodeanywhereAddressList = '';
          var postcodeanywhereloader = '';
        }
        else {
          // Create a lookup button.
          var postcodeanywhereLookupButton = '<input type="button" name="postcodeanywhere-lookup-button" id="postcodeanywhere-lookup-button" value="' +
                            Drupal.t(Drupal.settings.postcodeanywhere.submit_label_value) + '">';
          // Create address list list on the fly.
          var postcodeanywhereAddressList = '<div style="display:none;" size="10" name="postcodeanywhere-address-list" id="postcodeanywhere-address-list">';
          // Create spinner container.
          var postcodeanywhereloader = '<div id="postcodeloading" class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div><div class="message">Please wait...</div></div>';
        }

        // Append lookup button and address list to PCA wrapper.
        $(postcodeanywhereLookupButton).insertAfter(Drupal.settings.postcodeanywhere.id_postcode);
        $(postcodeanywhereloader).insertAfter(Drupal.settings.postcodeanywhere.id_postcode);
        $(postcodeanywhereAddressList).appendTo(Drupal.settings.postcodeanywhere.id_wrapper);

        // Add loading spinner div to end of PCA.
        $('#postcodeloading')
        // Hide it initially.
            .hide()
            .ajaxStart(function() {
                $(this).show();
            })
            .ajaxStop(function() {
                $(this).hide();
            });

        // Changes to PCA autocomplete widget.
        // Hide the manual fields on start
        $('.group-pca-autocomplete').find('#edit-field-address').hide();
        // Create the div which populates with the text version of the address.
        $('.group-pca-autocomplete').find('#edit-field-address').before('<div class="postcodeanywhere-autocomplete-output-text" id="postcodeanywhere-autocomplete-output-text"></div>');
        $('.group-pca-autocomplete').find('.postcodeanywhere-autocomplete-output-text').hide();
        $('.group-pca-autocomplete').find('.postcodeanywhere-autocomplete-output-text').html('<p class="thoroughfare pca-text"></p><p class="premise pca-text"></p><p class="postal-code pca-text"></p><p class="pca-change-address"><a href="#">Change Address</a></p>');

        // Add the onclick event to change the address.
        $('.group-pca-autocomplete').find('.pca-change-address').on('click','a',function(event){
          var pca_change_address = $(this);
          var pca_group = $(pca_change_address).closest('.group-pca-autocomplete');
          var pca_input_group = $(pca_group).find('.field-type-postcodeanywhere');
          $(pca_input_group).slideDown('Slow');
          // $(pca_group).find('.postcodeanywhere-autocomplete-output-text').hide();
        });


        if (typeof Drupal.jsAC != 'undefined') {
          // This function modifies the autocomplete on select event to populate the address fields.
          Drupal.jsAC.prototype.select = function (node) {

            this.input.value = this.input.value;

            // Set some selectors.
            var pca_input = this.input;
            var pca_id = $(node).data('autocompleteValue');
            var pca_input_group = $(pca_input).closest('.group-pca-autocomplete');
            var pca_output_div = $(pca_input_group).find('.postcodeanywhere-autocomplete-output-text');
            var outputAddress ='';

            // Clear the address fields.
            $(pca_input_group).find('input').val('');
            $(pca_input_group).find('.pca-text').html('');

            // If this is no-match then show the fields.
            if (pca_id == "no-match") {
              $(pca_input_group).find('#edit-field-address').slideDown('Slow');
              $(pca_input_group).find('.postcodeanywhere-autocomplete-output-text').hide();
              $('[class *=address-und-address-line-1').slideDown('Slow')
              $('[class *=address-und-address-line-2').slideDown('Slow')
              $('[class *=address-und-town').slideDown('Slow')
              $('[class *=add-address').show();
              $('[class *=cancel-address').show();

            }
            else if (!isNaN(pca_id)) {

              // Make sure this is hidden.
              $(pca_input_group).find('#edit-field-address').hide();
              $(pca_output_div).slideUp('Slow');

              // Call the PCA service to get a full address by ID.
              $.getJSON(Drupal.settings.basePath + "pca/retrievebyid/" + pca_id, function(data){
                if (data.length > 0 && data['error'] == null) {
                 if($('.pca-text').length<7){
                   outputAddress = $('<p class="thoroughfare pca-text">'+ data[0].Line1[0] + '</p><p class="premise pca-text">'+ data[0].Line2[0] +'</p><p class="premise pca-text">'+ data[0].PostTown[0] +'</p><p class="postal-code pca-text">'+ data[0].Postcode[0] +'</p><p class="pca-change-address"><a href="#!">Use another address</a></p>');

                   $('[class *=address-und-postcode').hide();
                 }

                  // Find the address field and populate them.
                  if (Drupal.settings.postcodeanywhere.addressfield) {

                    $(pca_input_group).find('.thoroughfare').val(data[0].Line1[0]);
                    $(pca_output_div).find('.thoroughfare').html(data[0].Line1[0]);

                    // Block element.
                    $(pca_input_group).find('.premise').val(data[0].Line2[0]);
                    $(pca_output_div).find('.premise').html(data[0].Line2[0]);
                    $(pca_input_group).find('.locality').val(data[0].County[0]);
                    $(pca_input_group).find('.state').val(data[0].PostTown[0]);
                    $(pca_input_group).find('.postal-code').val(data[0].Postcode[0]);
                    $(pca_output_div).find('.postal-code').html(data[0].Postcode[0]);
                    $(pca_input).val('');

                    $(pca_input).closest('.field-type-postcodeanywhere').slideUp('Slow',function(){
                      $(pca_output_div).slideDown('Slow');
                    });
                  } else {
                    // Set the values for non address field.
                    // Check if the results are strings.
                    if (typeof data[0].Company == 'string') {
                      $(Drupal.settings.postcodeanywhere.id_company).val(data[0].Company).change();
                      if ($(Drupal.settings.postcodeanywhere.addressfield)) {
                        $(Drupal.settings.postcodeanywhere.id_laddress - level2).val(data[0].PostTown).change();
                      }
                      else {
                        $(Drupal.settings.postcodeanywhere.id_line1).val(data[0].Line1).change();
                        $(Drupal.settings.postcodeanywhere.id_line2).val(data[0].Line2).change();
                        $(Drupal.settings.postcodeanywhere.id_line3).val(data[0].Line3).change();
                        $(Drupal.settings.postcodeanywhere.id_town).val(data[0].PostTown).change();
                      }
                      $(Drupal.settings.postcodeanywhere.id_county).val(data[0].County).change();
                      $(Drupal.settings.postcodeanywhere.id_postcode).val(data[0].Postcode).change();
                    }
                    // If the results are objects.
                    if (typeof data[0].Company == 'object') {
                      $(Drupal.settings.postcodeanywhere.id_company).val(data[0].Company[0]).change();
                      $(Drupal.settings.postcodeanywhere.id_line1).val(data[0].Line1[0]).change();
                      $(Drupal.settings.postcodeanywhere.id_line2).val(data[0].Line2[0]).change();
                      $(Drupal.settings.postcodeanywhere.id_line3).val(data[0].Line3[0]).change();
                      $(Drupal.settings.postcodeanywhere.id_town).val(data[0].PostTown[0]).change();
                      $(Drupal.settings.postcodeanywhere.id_county).val(data[0].County[0]).change();
                      $(Drupal.settings.postcodeanywhere.id_postcode).val(data[0].Postcode[0]).change();
                    }
                  }

                } // end: if(data)

              });
            } // end: else

          } // end: Drupal.jsAC
        }

        // Add onclick event to lookup button.
        $(Drupal.settings.postcodeanywhere.id_lookup_button).click(function() {
          if (!$(Drupal.settings.postcodeanywhere.id_postcode).val()) {
             alert(Drupal.t('Please supply a valid post code.'));
            $(Drupal.settings.postcodeanywhere.id_postcode).focus();
            return false;
          }
           else {
             $.getJSON(Drupal.settings.basePath + "pca/findbypostcode/" + $(Drupal.settings.postcodeanywhere.id_postcode).val(), function(data){
                var html = '';
                if (data != null) {
                  if (data['error'] != null) {
                    $(Drupal.settings.postcodeanywhere.id_company_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_line1_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_line2_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_line3_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_town_wrapper).show();
                    $(Drupal.settings.postcodeanywhere.id_county_wrapper).show();
                    alert(Drupal.t("Sorry there was an issue with the postcode lookup, please double check if your entry is valid.\n\nError: ") + data['error']);
                  }
                  else {
                    var len = data.length;
                    for (var i = 0; i < len; i++) {
                        html += '<input type="radio" value="' + data[i].Id + '" id="' + data[i].Id + '" name="postcodeanywhere-address" /><label for="' + data[i].Id + '">' + data[i].StreetAddress + ', ' + data[i].Place + '</label>';
                    }
                    $('#postcodeanywhere-address-list').html(html);
                    // $('#postcodeanywhere-address-list').slideDown();
                    $('#postcodeanywhere-address-list').show('slow');

                    // Add onchange event to address list.
                    $('input[name="postcodeanywhere-address"]').change(function() {
                      $.getJSON(Drupal.settings.basePath + "pca/retrievebyid/" + $(this).val(), function(data){
                        // Set the Values
                        // If the results are strings.
                        if (typeof data[0].Company == 'string') {
                          $(Drupal.settings.postcodeanywhere.id_company).val(data[0].Company).change();
                          if ($(Drupal.settings.postcodeanywhere.addressfield)) {
                            $(Drupal.settings.postcodeanywhere.id_laddress - level2).val(data[0].PostTown).change();
                          }
                          else {
                            $(Drupal.settings.postcodeanywhere.id_line1).val(data[0].Line1).change();
                            $(Drupal.settings.postcodeanywhere.id_line2).val(data[0].Line2).change();
                            $(Drupal.settings.postcodeanywhere.id_line3).val(data[0].Line3).change();
                            $(Drupal.settings.postcodeanywhere.id_town).val(data[0].PostTown).change();
                          }
                          $(Drupal.settings.postcodeanywhere.id_county).val(data[0].County).change();
                          $(Drupal.settings.postcodeanywhere.id_postcode).val(data[0].Postcode).change();
                        }
                        // If the results are objects.
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

                      // Hide the list.
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
          if ($(Drupal.settings.postcodeanywhere.id_country).val() == Drupal.settings.postcodeanywhere.id_country_uk_value) {
            $(Drupal.settings.postcodeanywhere.id_wrapper).show();
          }
          else {
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
