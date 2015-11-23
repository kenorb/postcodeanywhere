<?php
/*

  @file
    PostcodeAnywhere Interactive FindByLocalityId (v1.00)

  Lists address records for the given locality.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByLocalityId/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByLocalityId/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByLocalityId/v1.00/json.ws?Key=AA11-AA11-AA11-AA11&LocalityId=27312||B49&UserName=David
  Sample response: [{"StreetId":"0|27312|0|0","Street":"(no street name)","Place":"Coughton Alcester"}, {"StreetId":"0|27312|15548|1","Street":"Birmingham Road","Place":"Coughton Alcester"}, {"StreetId":"0|27312|4595|3","Street":"Sambourne Lane","Place":"Coughton Alcester"}]

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/findbylocalityid/1/

*/
class PostcodeAnywhere_Interactive_FindByLocalityId
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $LocalityId; //The Locality of the street to list the properties in.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_FindByLocalityId($Key, $LocalityId, $UserName)
   {
      $this->Key = $Key;
      $this->LocalityId = $LocalityId;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByLocalityId/v1.00/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&LocalityId=" . urlencode($this->LocalityId);
      $url .= "&UserName=" . urlencode($this->UserName);

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
// $pa = new PostcodeAnywhere_Interactive_FindByLocalityId_v1_00 ("AA11-AA11-AA11-AA11","27312||B49","David");
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
