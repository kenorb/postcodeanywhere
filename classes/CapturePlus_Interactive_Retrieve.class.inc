<?php

/*

  @file
    CapturePlus Interactive Retrieve (v2.10)

  Returns the full address details based on the Id.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/CapturePlus/Interactive/Retrieve/v2.10/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/CapturePlus/Interactive/Retrieve/v2.10/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/CapturePlus/Interactive/Retrieve/v2.10/json3.ws?Key=AA11-AA11-AA11-AA11&Id=GBR|26742631
  Sample response: {"Items":[{"Error":"1001","Description":"Id Invalid","Cause":"The Id parameter supplied was invalid.","Resolution":"Try again, using only IDs from the Find services."}]}

*/

class CapturePlus_Interactive_Retrieve
{

  // Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.
  // The key to use to authenticate to the service.
  private $Key;
  // The Id from a Find method to retrieve the details for.
  private $Id;
  // Holds the results of the query.
  private $Data;

  /**
   *
   */
  function CapturePlus_Interactive_Retrieve($Key, $Id) {

    $this->Key = $Key;
    $this->Id = $Id;
  }

  /**
   *
   */
  function MakeRequest() {

    $url = "http://services.postcodeanywhere.co.uk/CapturePlus/Interactive/Retrieve/v2.10/xmla.ws?";
    $url .= "&Key=" . urlencode($this->Key);
    $url .= "&Id=" . urlencode($this->Id);
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
        $this->Data[] = array('Id' => $item->attributes()->Id, 'DomesticId' => $item->attributes()->DomesticId, 'Language' => $item->attributes()->Language, 'LanguageAlternatives' => $item->attributes()->LanguageAlternatives, 'Department' => $item->attributes()->Department, 'Company' => $item->attributes()->Company, 'SubBuilding' => $item->attributes()->SubBuilding, 'BuildingNumber' => $item->attributes()->BuildingNumber, 'BuildingName' => $item->attributes()->BuildingName, 'SecondaryStreet' => $item->attributes()->SecondaryStreet, 'Street' => $item->attributes()->Street, 'Block' => $item->attributes()->Block, 'Neighbourhood' => $item->attributes()->Neighbourhood, 'District' => $item->attributes()->District, 'City' => $item->attributes()->City, 'Line1' => $item->attributes()->Line1, 'Line2' => $item->attributes()->Line2, 'Line3' => $item->attributes()->Line3, 'Line4' => $item->attributes()->Line4, 'Line5' => $item->attributes()->Line5, 'AdminAreaName' => $item->attributes()->AdminAreaName, 'AdminAreaCode' => $item->attributes()->AdminAreaCode, 'Province' => $item->attributes()->Province, 'ProvinceName' => $item->attributes()->ProvinceName, 'ProvinceCode' => $item->attributes()->ProvinceCode, 'PostalCode' => $item->attributes()->PostalCode, 'CountryName' => $item->attributes()->CountryName, 'CountryIso2' => $item->attributes()->CountryIso2, 'CountryIso3' => $item->attributes()->CountryIso3, 'CountryIsoNumber' => $item->attributes()->CountryIsoNumber, 'SortingNumber1' => $item->attributes()->SortingNumber1, 'SortingNumber2' => $item->attributes()->SortingNumber2, 'Barcode' => $item->attributes()->Barcode, 'POBoxNumber' => $item->attributes()->POBoxNumber, 'Label' => $item->attributes()->Label, 'Type' => $item->attributes()->Type, 'DataLevel' => $item->attributes()->DataLevel);
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
// $pa = new CapturePlus_Interactive_Retrieve_v2_10 ("AA11-AA11-AA11-AA11","GBR|26742631");
// $pa->MakeRequest();
// if ($pa->HasData())
// {
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Id"] . "<br/>";
//      echo $item["DomesticId"] . "<br/>";
//      echo $item["Language"] . "<br/>";
//      echo $item["LanguageAlternatives"] . "<br/>";
//      echo $item["Department"] . "<br/>";
//      echo $item["Company"] . "<br/>";
//      echo $item["SubBuilding"] . "<br/>";
//      echo $item["BuildingNumber"] . "<br/>";
//      echo $item["BuildingName"] . "<br/>";
//      echo $item["SecondaryStreet"] . "<br/>";
//      echo $item["Street"] . "<br/>";
//      echo $item["Block"] . "<br/>";
//      echo $item["Neighbourhood"] . "<br/>";
//      echo $item["District"] . "<br/>";
//      echo $item["City"] . "<br/>";
//      echo $item["Line1"] . "<br/>";
//      echo $item["Line2"] . "<br/>";
//      echo $item["Line3"] . "<br/>";
//      echo $item["Line4"] . "<br/>";
//      echo $item["Line5"] . "<br/>";
//      echo $item["AdminAreaName"] . "<br/>";
//      echo $item["AdminAreaCode"] . "<br/>";
//      echo $item["Province"] . "<br/>";
//      echo $item["ProvinceName"] . "<br/>";
//      echo $item["ProvinceCode"] . "<br/>";
//      echo $item["PostalCode"] . "<br/>";
//      echo $item["CountryName"] . "<br/>";
//      echo $item["CountryIso2"] . "<br/>";
//      echo $item["CountryIso3"] . "<br/>";
//      echo $item["CountryIsoNumber"] . "<br/>";
//      echo $item["SortingNumber1"] . "<br/>";
//      echo $item["SortingNumber2"] . "<br/>";
//      echo $item["Barcode"] . "<br/>";
//      echo $item["POBoxNumber"] . "<br/>";
//      echo $item["Label"] . "<br/>";
//      echo $item["Type"] . "<br/>";
//      echo $item["DataLevel"] . "<br/>";
//   }
// }.
