<?php

/*

  @file
    PostcodeAnywhere Interactive RetrieveChanges (v1.00)

  Lists the changes that have happened to the database over the given period of time.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveChanges/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveChanges/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveChanges/v1.00/json3.ws?Key=AA11-AA11-AA11-AA11&FromDate=20 October 2010&ToDate=21 October 2010&UserName=David
  Sample response: {"Items":[{"ChangedOn":"/Date(1287532800000)/","ChangeType":"Addition","ReasonForChange":"NewPostcodeOrAddress","Udprn":51697497,"Company":"","Department":"","Line1":"1 Redcroft Way","Line2":"","Line3":"","Line4":"","Line5":"","PostTown":"Polegate","County":"East Sussex","Postcode":"BN26 5FD","Mailsort":80211,"Barcode":"(BN265FD1A4)","Type":"Residential","DeliveryPointSuffix":"1A","SubBuilding":"","BuildingName":"","BuildingNumber":"1","PrimaryStreet":"Redcroft Way","SecondaryStreet":"","DoubleDependentLocality":"","DependentLocality":"","PoBox":"","PrimaryStreetName":"Redcroft","PrimaryStreetType":"Way","SecondaryStreetName":"","SecondaryStreetType":"","CountryName":"England"}]}


  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/retrievechanges/1/

*/

class PostcodeAnywhere_Interactive_RetrieveChanges
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $FromDate; //Start the report at this date.
   private $ToDate; //Finish the report at this date. If not supplied, today is assumed.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_RetrieveChanges($Key, $FromDate, $ToDate, $UserName)
   {
      $this->Key = $Key;
      $this->FromDate = $FromDate;
      $this->ToDate = $ToDate;
      $this->UserName = $UserName;
   }

  /**
   *
   */
  function MakeRequest() {

    $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveChanges/v1.00/xmla.ws?";
    $url .= "&Key=" . urlencode($this->Key);
    $url .= "&FromDate=" . urlencode($this->FromDate);
    $url .= "&ToDate=" . urlencode($this->ToDate);
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
        $this->Data[] = array('ChangedOn' => $item->attributes()->ChangedOn, 'ChangeType' => $item->attributes()->ChangeType, 'ReasonForChange' => $item->attributes()->ReasonForChange, 'Udprn' => $item->attributes()->Udprn, 'Company' => $item->attributes()->Company, 'Department' => $item->attributes()->Department, 'Line1' => $item->attributes()->Line1, 'Line2' => $item->attributes()->Line2, 'Line3' => $item->attributes()->Line3, 'Line4' => $item->attributes()->Line4, 'Line5' => $item->attributes()->Line5, 'PostTown' => $item->attributes()->PostTown, 'County' => $item->attributes()->County, 'Postcode' => $item->attributes()->Postcode, 'Mailsort' => $item->attributes()->Mailsort, 'Barcode' => $item->attributes()->Barcode, 'Type' => $item->attributes()->Type, 'DeliveryPointSuffix' => $item->attributes()->DeliveryPointSuffix, 'SubBuilding' => $item->attributes()->SubBuilding, 'BuildingName' => $item->attributes()->BuildingName, 'BuildingNumber' => $item->attributes()->BuildingNumber, 'PrimaryStreet' => $item->attributes()->PrimaryStreet, 'SecondaryStreet' => $item->attributes()->SecondaryStreet, 'DoubleDependentLocality' => $item->attributes()->DoubleDependentLocality, 'DependentLocality' => $item->attributes()->DependentLocality, 'PoBox' => $item->attributes()->PoBox, 'PrimaryStreetName' => $item->attributes()->PrimaryStreetName, 'PrimaryStreetType' => $item->attributes()->PrimaryStreetType, 'SecondaryStreetName' => $item->attributes()->SecondaryStreetName, 'SecondaryStreetType' => $item->attributes()->SecondaryStreetType, 'CountryName' => $item->attributes()->CountryName);
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
// $pa = new PostcodeAnywhere_Interactive_RetrieveChanges_v1_00 ("AA11-AA11-AA11-AA11","20 October 2010","21 October 2010","David");
// $pa->MakeRequest();
// if ($pa->HasData())
// {
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["ChangedOn"] . "<br/>";
//      echo $item["ChangeType"] . "<br/>";
//      echo $item["ReasonForChange"] . "<br/>";
//      echo $item["Udprn"] . "<br/>";
//      echo $item["Company"] . "<br/>";
//      echo $item["Department"] . "<br/>";
//      echo $item["Line1"] . "<br/>";
//      echo $item["Line2"] . "<br/>";
//      echo $item["Line3"] . "<br/>";
//      echo $item["Line4"] . "<br/>";
//      echo $item["Line5"] . "<br/>";
//      echo $item["PostTown"] . "<br/>";
//      echo $item["County"] . "<br/>";
//      echo $item["Postcode"] . "<br/>";
//      echo $item["Mailsort"] . "<br/>";
//      echo $item["Barcode"] . "<br/>";
//      echo $item["Type"] . "<br/>";
//      echo $item["DeliveryPointSuffix"] . "<br/>";
//      echo $item["SubBuilding"] . "<br/>";
//      echo $item["BuildingName"] . "<br/>";
//      echo $item["BuildingNumber"] . "<br/>";
//      echo $item["PrimaryStreet"] . "<br/>";
//      echo $item["SecondaryStreet"] . "<br/>";
//      echo $item["DoubleDependentLocality"] . "<br/>";
//      echo $item["DependentLocality"] . "<br/>";
//      echo $item["PoBox"] . "<br/>";
//      echo $item["PrimaryStreetName"] . "<br/>";
//      echo $item["PrimaryStreetType"] . "<br/>";
//      echo $item["SecondaryStreetName"] . "<br/>";
//      echo $item["SecondaryStreetType"] . "<br/>";
//      echo $item["CountryName"] . "<br/>";
//   }
// }.
