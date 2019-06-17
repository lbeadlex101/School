<%@ Page Title="Home Page" Language="VB" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.vb" Inherits="MyWebPart._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">


    <asp:WebPartManager ID="WebPartManager2" runat="server">     </asp:WebPartManager> 
 
      <asp:WebPartZone ID="WebPartZoneNorth" runat="server"         HeaderText="North Zone" style="width: 700px; height: auto">       </asp:WebPartZone> 
 
      <asp:WebPartZone ID="WebPartZoneWest" runat="server"         HeaderText="West Zone" style="width: 300px; float: left; height: 300px">
          <ZoneTemplate>
              <asp:Calendar ID="Calendar1" runat="server"></asp:Calendar>
          </ZoneTemplate>
    </asp:WebPartZone> 
 
      <asp:WebPartZone ID="WebPartZoneCenter" runat="server"         HeaderText="Center Zone"         style="width: 400px; float: left; height: 300px">
          <ZoneTemplate>
              <asp:Image ID="Image1" runat="server" />
          </ZoneTemplate>
    </asp:WebPartZone> 
 
      <asp:WebPartZone ID="WebPartZoneSouth" runat="server"         HeaderText="South Zone" style="width: 700px; height: auto;">       </asp:WebPartZone> 

</asp:Content>
