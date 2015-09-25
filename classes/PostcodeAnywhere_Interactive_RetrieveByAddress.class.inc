<?php

/*

  @file
    PostcodeAnywhere Interactive RetrieveByAddress (v1.20)

  Returns the full address details based on the address.
  Includes country name based on postcode area and the thoroughfare name components

  SOAP WSDL

  Standard HTTP: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveByAddress/v1.20/wsdlnew.ws
  Secure HTTPS: https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveByAddress/v1.20/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveByAddress/v1.20/json.ws?Key=AA11-AA11-AA11-AA11&Address=Enigma House, Hallow, WR2 6NJ&Company=&UserName=David
  Sample response: [{"Udprn":"26742629","Company":"","Department":"","Line1":"Monkwood House","Line2":"Moseley Road","Line3":"Hallow","Line4":"","Line5":"","PostTown":"Worcester","County":"Worcestershire","Postcode":"WR2 6NJ","Mailsort":"94141","Barcode":"(WR26NJ3LE)","Type":"Residential","DeliveryPointSuffix":"3L","SubBuilding":"","BuildingName":"Monkwood House","BuildingNumber":"","PrimaryStreet":"Moseley Road","SecondaryStreet":"","DoubleDependentLocality":"","DependentLocality":"Hallow","PoBox":"","PrimaryStreetName":"Moseley","PrimaryStreetType":"Road","SecondaryStreetName":"","SecondaryStreetType":"","CountryName":"England","Confidence":"0.51"}]

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/retrievebyaddress/1.2/


*/

class PostcodeAnywhere_Interactive_RetrieveByAddress
{

   //Includes country name based on postcode area and the thoroughfare name components
   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $Address; //The address to find. Separate the address lines with commas.
   private $Company; //The name of the company name. Ideally not part of the address
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_RetrieveByAddress_v1_20($Key, $Address, $Company, $UserName)
   {
      $this->Key = $Key;
      $this->Address = $Address;
      $this->Company = $Company;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveByAddress/v1.20/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&Address=" . urlencode($this->Address);
      $url .= "&Company=" . urlencode($this->Company);
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
             $this->Data[] = array('Udprn'=>$item->attributes()->Udprn,'Company'=>$item->attributes()->Company,'Department'=>$item->attributes()->Department,'Line1'=>$item->attributes()->Line1,'Line2'=>$item->attributes()->Line2,'Line3'=>$item->attributes()->Line3,'Line4'=>$item->attributes()->Line4,'Line5'=>$item->attributes()->Line5,'PostTown'=>$item->attributes()->PostTown,'County'=>$item->attributes()->County,'Postcode'=>$item->attributes()->Postcode,'Mailsort'=>$item->attributes()->Mailsort,'Barcode'=>$item->attributes()->Barcode,'Type'=>$item->attributes()->Type,'DeliveryPointSuffix'=>$item->attributes()->DeliveryPointSuffix,'SubBuilding'=>$item->attributes()->SubBuilding,'BuildingName'=>$item->attributes()->BuildingName,'BuildingNumber'=>$item->attributes()->BuildingNumber,'PrimaryStreet'=>$item->attributes()->PrimaryStreet,'SecondaryStreet'=>$item->attributes()->SecondaryStreet,'DoubleDependentLocality'=>$item->attributes()->DoubleDependentLocality,'DependentLocality'=>$item->attributes()->DependentLocality,'PoBox'=>$item->attributes()->PoBox,'PrimaryStreetName'=>$item->attributes()->PrimaryStreetName,'PrimaryStreetType'=>$item->attributes()->PrimaryStreetType,'SecondaryStreetName'=>$item->attributes()->SecondaryStreetName,'SecondaryStreetType'=>$item->attributes()->SecondaryStreetType,'CountryName'=>$item->attributes()->CountryName,'Confidence'=>$item->attributes()->Confidence);
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
//$pa = new PostcodeAnywhere_Interactive_RetrieveByAddress_v1_20 ("AA11-AA11-AA11-AA11","Enigma House, Hallow, WR2 6NJ","","David");
//$pa->MakeRequest();
//if ($pa->HasData())
//{
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
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
//      echo $item["Confidence"] . "<br/>";
//   }
//}
