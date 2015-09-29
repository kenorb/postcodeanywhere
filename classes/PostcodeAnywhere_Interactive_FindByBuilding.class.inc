<?php

/*
  @file
    PostcodeAnywhere Interactive FindByBuilding (v1.00)

  Finds address records matching the given building details.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByBuilding/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByBuilding/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByBuilding/v1.00/json.ws?Key=AA11-AA11-AA11-AA11&Building=Enigma House&LocalityOrPartialPostcode=WR2&UserName=David

  Sample response: [{"Id":"26743556.00","StreetAddress":"Enigma House Crown East Lane","Place":"Lower Broadheath Worcester"}]

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/findbybuilding/1/

*/

class PostcodeAnywhere_Interactive_FindByBuilding
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $Building; //The name of the building to find.
   private $LocalityOrPartialPostcode; //The name of the locality or partial postcode.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_FindByBuilding($Key, $Building, $LocalityOrPartialPostcode, $UserName)
   {
      $this->Key = $Key;
      $this->Building = $Building;
      $this->LocalityOrPartialPostcode = $LocalityOrPartialPostcode;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByBuilding/v1.00/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&Building=" . urlencode($this->Building);
      $url .= "&LocalityOrPartialPostcode=" . urlencode($this->LocalityOrPartialPostcode);
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
//$pa = new PostcodeAnywhere_Interactive_FindByBuilding_v1_00 ("AA11-AA11-AA11-AA11","Enigma House","WR2","David");
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

