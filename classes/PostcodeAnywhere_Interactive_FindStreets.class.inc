<?php

/*

  @file
    PostcodeAnywhere Interactive FindStreets (v1.00)

  Lists streets matching the given search criteria.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindStreets/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindStreets/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindStreets/v1.00/json3.ws?Key=AA11-AA11-AA11-AA11&Street=Moseley&LocalityOrPartialPostcode=WR2&UserName=David
  Sample response: {"Items":[{"StreetId":"0|30389|5998|1","Street":"Moseley Road","Place":"Hallow Worcester"}]}

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/findstreets/1/

*/

class PostcodeAnywhere_Interactive_FindStreets
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $Street; //The name of the street to find. If left blank, a partial postcode must be supplied in LocalityOrPartialPostcode and all streets in that postcode will be listed.
   private $LocalityOrPartialPostcode; //The name of the locality or partial postcode. If left blank, all streets in the country are listed.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_FindStreets($Key, $Street, $LocalityOrPartialPostcode, $UserName)
   {
      $this->Key = $Key;
      $this->Street = $Street;
      $this->LocalityOrPartialPostcode = $LocalityOrPartialPostcode;
      $this->UserName = $UserName;
   }

  /**
   *
   */
  function MakeRequest() {

    $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindStreets/v1.00/xmla.ws?";
    $url .= "&Key=" . urlencode($this->Key);
    $url .= "&Street=" . urlencode($this->Street);
    $url .= "&LocalityOrPartialPostcode=" . urlencode($this->LocalityOrPartialPostcode);
    $url .= "&UserName=" . urlencode($this->UserName);
    $url = postcodeanywhere_parse_url($url);

    // Make the request to Postcode Anywhere and parse the XML returned.
    $file = simplexml_load_file($url);

    // Check for an error, if there is one then throw an exception.
    if ($file->Columns->Column->attributes()->Name == "Error") {
      throw new Exception("[ID] " . $file->Rows->Row->attributes()->Error . " [DESCRIPTION] " . $file->Rows->Row->attributes()->Description . " [CAUSE] " . $file->Rows->Row->attributes()->Cause . " [RESOLUTION] " . $file->Rows->Row->attributes()->Resolution);
    }

    // Copy the data.
    if (!empty($file->Rows)) {
      foreach ($file->Rows->Row as $item) {
        $this->Data[] = array('StreetId' => $item->attributes()->StreetId, 'Street' => $item->attributes()->Street, 'Place' => $item->attributes()->Place);
      }
    }
  }

  /**
   *
   */
  function HasData() {

    if (!empty($this->Data)) {
      return $this->Data;
    }
    return FALSE;
  }

}

// Example usage
// -------------
// $pa = new PostcodeAnywhere_Interactive_FindStreets_v1_00 ("AA11-AA11-AA11-AA11","Moseley","WR2","David");
// $pa->MakeRequest();
// if ($pa->HasData())
// {
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["StreetId"] . "<br/>";
//      echo $item["Street"] . "<br/>";
//      echo $item["Place"] . "<br/>";
//   }
// }.
