<?php

/*

  @file
    PostcodeAnywhere Interactive FindByStreetId (v1.00)

  Lists address records for the given street.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByStreetId/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByStreetId/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByStreetId/v1.00/json3.ws?Key=AA11-AA11-AA11-AA11&StreetId=0|30389|5998|1&UserName=David
  Sample response: {"Items":[{"Id":"26742650.00","StreetAddress":"Bridgehouse Property Consultants","Place":"Unit 3 Elgar Business Centre Moseley Road Hallow Worcester"},{"Id":"26742633.00","StreetAddress":"Britannia Site Solutions Ltd","Place":"Britannia House Unit 11-13 Elgar Business Centre Moseley Road Hallow Worcester"},{"Id":"1000964071.00","StreetAddress":"Care 4 Health","Place":"Unit 8 Elgar Business Centre Moseley Road Hallow Worcester"},{"Id":"52489478.00","StreetAddress":"Child Care Bureau","Place":"Unit 4 Elgar Business Centre Moseley Road Hallow Worcester"},{"Id":"53701343.00","StreetAddress":"Child Care Bureau","Place":"Britannia House Unit 11-13 Elgar Business Centre Moseley Road Hallow Worcester"},{"Id":"50421922.00","StreetAddress":"Clearview","Place":"Unit 14-15 Elgar Business Centre Moseley Road Hallow Worcester"},{"Id":"26742661.00","StreetAddress":"The Willows Moseley Road","Place":"Hallow Worcester"},{"Id":"26742660.00","StreetAddress":"Whitegates Moseley Road","Place":"Hallow Worcester"},{"Id":"26742621.00","StreetAddress":"Woodmanton Cottage Moseley Road","Place":"Hallow Worcester"},{"Id":"26742622.00","StreetAddress":"York House Moseley Road","Place":"Hallow Worcester"}]}

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/findbystreetid/1/


*/

class PostcodeAnywhere_Interactive_FindByStreetId
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $StreetId; //The StreetId of the street to list the properties in.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_FindByStreetId_v1_00($Key, $StreetId, $UserName)
   {
      $this->Key = $Key;
      $this->StreetId = $StreetId;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByStreetId/v1.00/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&StreetId=" . urlencode($this->StreetId);
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
//$pa = new PostcodeAnywhere_Interactive_FindByStreetId_v1_00 ("AA11-AA11-AA11-AA11","0|30389|5998|1","David");
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

