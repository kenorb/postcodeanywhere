<?php
/*

  @file
    CapturePlus Interactive Find (v2.10)

  Find addresses matching the search term.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/CapturePlus/Interactive/Find/v2.10/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/CapturePlus/Interactive/Find/v2.10/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/CapturePlus/Interactive/Find/v2.10/json3.ws?Key=AA11-AA11-AA11-AA11&SearchTerm=wr2 6nj&LastId=&SearchFor=Everything&Country=GBR&LanguagePreference=EN&MaxSuggestions=&MaxResults=

  Sample response: {"Items":[{"Id":"GBR|26742664","Text":"WR2 6NJ, 1, The Cottages, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742665","Text":"WR2 6NJ, 1, Wylcotts, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742666","Text":"WR2 6NJ, 2, The Cottages, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|52269655","Text":"WR2 6NJ, 2, Wylcotts, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742647","Text":"WR2 6NJ, (Denton), Moseley Cottage, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|53015862","Text":"WR2 6NJ, (Roberts), Moseley Cottage, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742627","Text":"WR2 6NJ, Beaumont, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742650","Text":"WR2 6NJ, Bridgehouse Property Consultants, Unit 3, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742633","Text":"WR2 6NJ, Britannia Site Solutions Ltd, Britannia House Unit 11-13, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742628","Text":"WR2 6NJ, Brook Cottage, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|1000964071","Text":"WR2 6NJ, Care 4 Health, Unit 8, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|53701343_1357973","Text":"WR2 6NJ, Child Care Bureau Ltd, Child Care Bureau, Britannia House Unit 11-13, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|53701343","Text":"WR2 6NJ, Child Care Bureau, Britannia House Unit 11-13, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|52489478","Text":"WR2 6NJ, Child Care Bureau, Unit 4, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|50421922","Text":"WR2 6NJ, Clearview, Unit 14-15, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742630","Text":"WR2 6NJ, Essfield, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742631","Text":"WR2 6NJ, Fairfields, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742634","Text":"WR2 6NJ, Flatten Bank, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742635","Text":"WR2 6NJ, Four Acres, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742639","Text":"WR2 6NJ, Holly Cottage, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742638","Text":"WR2 6NJ, Hollymount, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742640","Text":"WR2 6NJ, Inglemere House, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742641","Text":"WR2 6NJ, Ivy Cottage, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742642","Text":"WR2 6NJ, Kothi, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742643","Text":"WR2 6NJ, Leacroft, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742644","Text":"WR2 6NJ, Lyncroft, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742645","Text":"WR2 6NJ, Maryville, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742646","Text":"WR2 6NJ, Microtrol Ltd, Unit 16, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742686","Text":"WR2 6NJ, Mill House, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742629","Text":"WR2 6NJ, Monkwood House, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742648","Text":"WR2 6NJ, Moseley Saw Mills, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742653","Text":"WR2 6NJ, Opus Claims Solutions Ltd, Premier House, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742652","Text":"WR2 6NJ, Orchard View, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742626","Text":"WR2 6NJ, Pool House, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742636","Text":"WR2 6NJ, Primrose Cottage, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742654","Text":"WR2 6NJ, Pump Cottage, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742655","Text":"WR2 6NJ, Robin Pearce Plants, Worlds End Nurseries, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742656","Text":"WR2 6NJ, Rose Cottage, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742657","Text":"WR2 6NJ, Rose Dale, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742658","Text":"WR2 6NJ, Sandfield, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742659","Text":"WR2 6NJ, Stilecroft, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742637","Text":"WR2 6NJ, The Haven, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742649","Text":"WR2 6NJ, The Old Bakery, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742661","Text":"WR2 6NJ, The Willows, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742625","Text":"WR2 6NJ, Time Code Systems, Unit 6, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|51501819","Text":"WR2 6NJ, Unit 9, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742660","Text":"WR2 6NJ, Whitegates, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742667","Text":"WR2 6NJ, Worcestershire Federation of Wi\u0027s, Unit 7, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742662","Text":"WR2 6NJ, Worlds End Nurseries, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742663","Text":"WR2 6NJ, Wychbury Engineering Services Ltd, Unit 2, Elgar Business Centre, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"},{"Id":"GBR|26742663_1069024","Text":"WR2 6NJ, Wychbury Engineering Services Ltd, Unit 2, W E S, Moseley Road, Hallow, Worcester ","Highlight":"","Cursor":0,"Description":"","Next":"Retrieve"}]}

  Demo: http://www.pcapredict.com/support/webservice/captureplus/interactive/find/2.1/

*/

class CapturePlus_Interactive_Find
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $SearchTerm; //The search term to find. If the LastId is provided, the SearchTerm searches within the results from the LastId.
   private $LastId; //The Id from a previous Find or FindByPosition.
   private $SearchFor; //Filters the search results.
   private $Country; //The name or ISO 2 or 3 character code for the country to search in. Most country names will be recognised but the use of the ISO country code is recommended for clarity.
   private $LanguagePreference; //The 2 or 4 character language preference identifier e.g. (en, en-gb, en-us etc).
   private $MaxSuggestions; //The maximum number of autocomplete suggestions to return.
   private $MaxResults; //The maximum number of retrievable address results to return.
   private $Data; //Holds the results of the query

   function CapturePlus_Interactive_Find($Key, $SearchTerm, $LastId, $SearchFor, $Country, $LanguagePreference, $MaxSuggestions, $MaxResults)
   {
      $this->Key = $Key;
      $this->SearchTerm = $SearchTerm;
      $this->LastId = $LastId;
      $this->SearchFor = $SearchFor;
      $this->Country = $Country;
      $this->LanguagePreference = $LanguagePreference;
      $this->MaxSuggestions = $MaxSuggestions;
      $this->MaxResults = $MaxResults;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/CapturePlus/Interactive/Find/v2.10/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&SearchTerm=" . urlencode($this->SearchTerm);
      $url .= "&LastId=" . urlencode($this->LastId);
      $url .= "&SearchFor=" . urlencode($this->SearchFor);
      $url .= "&Country=" . urlencode($this->Country);
      $url .= "&LanguagePreference=" . urlencode($this->LanguagePreference);
      $url .= "&MaxSuggestions=" . urlencode($this->MaxSuggestions);
      $url .= "&MaxResults=" . urlencode($this->MaxResults);

      //Make the request to Postcode Anywhere and parse the XML returned
      $file = simplexml_load_file($url);

      //Check for an error, if there is one then throw an exception
      if ($file->Columns->Column->attributes()->Name == "Error") 
      {
         throw new Exception("[ID] " . $file->Rows->Row->attributes()->Error . " [DESCRIPTION] " . $file->Rows->Row->attributes()->Description . " [CAUSE] " . $file->Rows->Row->attributes()->Cause . " [RESOLUTION] " . $file->Rows->Row->attributes()->Resolution);
      }

      //Copy the data
      if ( !empty($file->Rows) )
      {
         foreach ($file->Rows->Row as $item)
         {
             $this->Data[] = array('Id'=>$item->attributes()->Id,'Text'=>$item->attributes()->Text,'Highlight'=>$item->attributes()->Highlight,'Cursor'=>$item->attributes()->Cursor,'Description'=>$item->attributes()->Description,'Next'=>$item->attributes()->Next);
         }
      }
   }

   function HasData()
   {
      if ( !empty($this->Data) )
      {
         return $this->Data;
      }
      return false;
   }

}

//Example usage
//-------------
//$pa = new CapturePlus_Interactive_Find_v2_10 ("AA11-AA11-AA11-AA11","wr2 6nj","","Everything","GBR","EN","","");
//$pa->MakeRequest();
//if ($pa->HasData())
//{
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Id"] . "<br/>";
//      echo $item["Text"] . "<br/>";
//      echo $item["Highlight"] . "<br/>";
//      echo $item["Cursor"] . "<br/>";
//      echo $item["Description"] . "<br/>";
//      echo $item["Next"] . "<br/>";
//   }
//}
