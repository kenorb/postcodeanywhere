<?php

/*

  @file
    PostcodeAnywhere Interactive FindByPostcode (v1.00)

  Lists address records for the given postcode.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPostcode/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPostcode/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPostcode/v1.00/json.ws?Key=AA11-AA11-AA11-AA11&Postcode=WR2 6NJ&UserName=David
  Sample response:
  [{"Id":"26742650.00","StreetAddress":"Bridgehouse Property Consultants","Place":"Unit 3 Elgar Business Centre Moseley Road Hallow Worcester"},
  {"Id":"26742633.00","StreetAddress":"Britannia Site Solutions Ltd","Place":"Britannia House Unit 11-13 Elgar Business Centre Moseley Road Hallow Worcester"},
  {"Id":"1000964071.00","StreetAddress":"Care 4 Health","Place":"Unit 8 Elgar Business Centre Moseley Road Hallow Worcester"},
  "Id":"26742649.00","StreetAddress":"The Old Bakery Moseley Road","Place":"Hallow Worcester"},
  {"Id":"26742661.00","StreetAddress":"The Willows Moseley Road","Place":"Hallow Worcester"},
  {"Id":"26742660.00","StreetAddress":"Whitegates Moseley Road","Place":"Hallow Worcester"}]

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/findbypostcode/1/

*/

class PostcodeAnywhere_Interactive_FindByPostcode
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $Postcode; //The postcode to search with find.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_FindByPostcode_v1_00($Key, $Postcode, $UserName)
   {
      $this->Key = $Key;
      $this->Postcode = $Postcode;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPostcode/v1.00/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&Postcode=" . urlencode($this->Postcode);
      $url .= "&UserName=" . urlencode($this->UserName);

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
             $this->Data[] = array('Id'=>$item->attributes()->Id,'StreetAddress'=>$item->attributes()->StreetAddress,'Place'=>$item->attributes()->Place);
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
//$pa = new PostcodeAnywhere_Interactive_FindByPostcode_v1_00 ("AA11-AA11-AA11-AA11","WR2 6NJ","David");
//$pa->MakeRequest();
//if ($pa->HasData())
//{
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Id"] . "<br/>";
//      echo $item["StreetAddress"] . "<br/>";
//      echo $item["Place"] . "<br/>";
//   }
//}

