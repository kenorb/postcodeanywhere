
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Configuration


INTRODUCTION
------------

 Project URL: http://drupal.org/project/postcodeanywhere
 GitHub URL:  https://github.com/mycognitive/postcodeanywhere

 The postcode anywhere module allows you to provide automatic UK address lookup
 on your drupal site. 
 
 It is a 3rd party integration with the PCA Predict (formerly Postcode Anywhere) service,
 run by: http://www.pcapredict.com/

 In order to use this module, you must have an account with the service provider.
 Support regarding accounts and licence keys must be directed to PCA Predict.

 During development, to avoid service charges, a test postcode of WR2 6NJ can
 be used freely (Correct at the time of writing).
 
 The module modifies the targetted forms, hiding the majority of form elements,
 and adds a "Find address" button next to the postcode field.
 When completed and submitted, the module loads and displays a list of addresses
 registered to that UK postcode. When the user selects their address from the
 list, the address form is re-displayed, complete with the selected details, as
 configured on the module admin page.
 
 In the event of errors or problems with the service, the module uses a
 Javascript alert to warn the user, and invites them to complete their address
 manually. Address details, once used, are cached locally to help manage service 
 interuptions and to improve performance.


INSTALLATION
------------

 1. Copy the postcodeanywhere directory to sites/SITENAME/modules/contrib directory.
 
 2. Enable the module and confirm your permissions. 
 
 3. Navigate to /admin/config/content/postcodeanywhere and follow the configuration 
    guidelines below.
 
 
 CONFIGURATION
 -------------

 * Log into your http://www.pcapredict.com/ account, and navigate to your licence 
   key list. Copy the Web service key for Website Tools and paste it into the 
   web service key box exactly as it appears. It should be of the format:
   AA11-AA11-AA11-AA11.
   
 * The default URL is correct at the time of release, but can be re-configured
   if nessesary.
   
 * Instruct module when to look for a postcode entry form. For example,
   to include the feature only on the site registration page, select "Show only
   on the listed pages" and enter "user/register" in the pages box.
   
 * In the form selectors box you need to tell the module which input elements
   will be providing the postcode and which elements hold the results.
   
   The postcode wrapper tells the module where to include the "Find address"
   form, and the postcode Id must be the actual text input element that will 
   contain the postcode value.
   
   The additional wrapper values are used to hide the other address form
   elements initally, and then display them once populated. The ID values are
   used to inject the values onto the form when they are selected, ready for
   form submission. Missing or irrelevant values can be left blank.
      
 * The module will only attempt to lookup UK postcodes, so if a country
   selection box is available on the form, and given a target ID, you must enter
   the key for the United Kingdom option here.

