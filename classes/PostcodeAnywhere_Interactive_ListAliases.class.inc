<?php

/*

  @file
    PostcodeAnywhere Interactive ListAliases (v1.10)

  Lists the known aliases for a given address. These may include additional place names, local spelling or alternative building names and company names.
  Now supports searching by postcode.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/ListAliases/v1.10/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/ListAliases/v1.10/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/ListAliases/v1.10/json.ws?Key=AA11-AA11-AA11-AA11&IdOrPostcode=9395987.00&UserName=David
  Sample respnse: [{"Type":"Place","Name":"Greenfield"}, {"Type":"Place","Name":"Budhill"}, {"Type":"TraditionalCounty","Name":"Lanarkshire"}, {"Type":"AdministrativeCounty","Name":"City of Glasgow"}]
  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/listaliases/1.1/

*/

class PostcodeAnywhere_Interactive_ListAliases
{

   //Now supports searching by postcode.
   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $IdOrPostcode; //The Id from a Find method to retrieve the details for or a postcode.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_ListAliases($Key, $IdOrPostcode, $UserName)
   {
      $this->Key = $Key;
      $this->IdOrPostcode = $IdOrPostcode;
      $this->UserName = $UserName;
   }

  /**
   *
   */
  function MakeRequest() {

    $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/ListAliases/v1.10/xmla.ws?";
    $url .= "&Key=" . urlencode($this->Key);
    $url .= "&IdOrPostcode=" . urlencode($this->IdOrPostcode);
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
        $this->Data[] = array('Type' => $item->attributes()->Type, 'Name' => $item->attributes()->Name);
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
// $pa = new PostcodeAnywhere_Interactive_ListAliases_v1_10 ("AA11-AA11-AA11-AA11","9395987.00","David");
// $pa->MakeRequest();
// if ($pa->HasData())
// {
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Type"] . "<br/>";
//      echo $item["Name"] . "<br/>";
//   }
// }.
