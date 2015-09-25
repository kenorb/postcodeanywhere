<?php

/*

  @file
    PostcodeAnywhere Interactive RetrieveHistoryById (v1.00)

  Returns all historical versions of this address (from November 2009).
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveHistoryById/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveHistoryById/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveHistoryById/v1.00/json.ws?Key=AA11-AA11-AA11-AA11&Id=26778735.00&UserName=David
  Sample response: [{"Udprn":"26778735","Company":"","Department":"","Line1":"Humble Bee Hall","Line2":"Stonehouse Lane","Line3":"Bringsty","Line4":"","Line5":"","PostTown":"Worcester","County":"Herefordshire","Postcode":"WR6 5TG","Mailsort":"70113","Barcode":"(WR65TG1JG)","Type":"Residential","DeliveryPointSuffix":"1J","SubBuilding":"","BuildingName":"Humble Bee Hall","BuildingNumber":"","PrimaryStreet":"Stonehouse Lane","SecondaryStreet":"","DoubleDependentLocality":"","DependentLocality":"Bringsty","PoBox":"","ChangedOn":"2009-11-26","ChangeType":"Update"},{"Udprn":"26778735","Company":"","Department":"","Line1":"Humble Bee Hall","Line2":"Stonehouse Lane","Line3":"Bringsty","Line4":"","Line5":"","PostTown":"Worcester","County":"Herefordshire","Postcode":"WR6 5TF","Mailsort":"94133","Barcode":"(WR65TF2EB)","Type":"Residential","DeliveryPointSuffix":"2E","SubBuilding":"","BuildingName":"Humble Bee Hall","BuildingNumber":"","PrimaryStreet":"Stonehouse Lane","SecondaryStreet":"","DoubleDependentLocality":"","DependentLocality":"Bringsty","PoBox":"","ChangedOn":"2015-09-25 15:52:14","ChangeType":"Current"}]
  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/retrievehistorybyid/1/

*/

class PostcodeAnywhere_Interactive_RetrieveHistoryById
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $Id; //The Id from a Find method to retrieve the details for.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_RetrieveHistoryById_v1_00($Key, $Id, $UserName)
   {
      $this->Key = $Key;
      $this->Id = $Id;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveHistoryById/v1.00/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&Id=" . urlencode($this->Id);
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
             $this->Data[] = array('Udprn'=>$item->attributes()->Udprn,'Company'=>$item->attributes()->Company,'Department'=>$item->attributes()->Department,'Line1'=>$item->attributes()->Line1,'Line2'=>$item->attributes()->Line2,'Line3'=>$item->attributes()->Line3,'Line4'=>$item->attributes()->Line4,'Line5'=>$item->attributes()->Line5,'PostTown'=>$item->attributes()->PostTown,'County'=>$item->attributes()->County,'Postcode'=>$item->attributes()->Postcode,'Mailsort'=>$item->attributes()->Mailsort,'Barcode'=>$item->attributes()->Barcode,'Type'=>$item->attributes()->Type,'DeliveryPointSuffix'=>$item->attributes()->DeliveryPointSuffix,'SubBuilding'=>$item->attributes()->SubBuilding,'BuildingName'=>$item->attributes()->BuildingName,'BuildingNumber'=>$item->attributes()->BuildingNumber,'PrimaryStreet'=>$item->attributes()->PrimaryStreet,'SecondaryStreet'=>$item->attributes()->SecondaryStreet,'DoubleDependentLocality'=>$item->attributes()->DoubleDependentLocality,'DependentLocality'=>$item->attributes()->DependentLocality,'PoBox'=>$item->attributes()->PoBox,'ChangedOn'=>$item->attributes()->ChangedOn,'ChangeType'=>$item->attributes()->ChangeType);
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
//$pa = new PostcodeAnywhere_Interactive_RetrieveHistoryById_v1_00 ("AA11-AA11-AA11-AA11","26778735.00","David");
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
//      echo $item["ChangedOn"] . "<br/>";
//      echo $item["ChangeType"] . "<br/>";
//   }
//}

