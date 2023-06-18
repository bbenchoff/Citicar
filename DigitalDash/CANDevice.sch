<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="DT13-4P">
<description>&lt;HDR, 4P, GRY, RA, NI/CU RECEPTACLE HEADER 4 PIN 90 DEG DT SERIES&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by SamacSys&lt;/author&gt;</description>
<packages>
<package name="DT134P">
<description>&lt;b&gt;DT13-4P-1&lt;/b&gt;&lt;br&gt;
</description>
<pad name="1" x="0" y="0" drill="1.76" diameter="2.64"/>
<pad name="2" x="4.45" y="0" drill="1.76" diameter="2.64"/>
<pad name="3" x="4.45" y="-6.35" drill="1.76" diameter="2.64"/>
<pad name="4" x="0" y="-6.35" drill="1.76" diameter="2.64"/>
<pad name="MH1" x="-6.425" y="-1.02" drill="2.99" diameter="4.485"/>
<pad name="MH2" x="10.875" y="-1.02" drill="2.99" diameter="4.485"/>
<pad name="MH3" x="2.225" y="-12.45" drill="2.99" diameter="4.485"/>
<text x="2.225" y="-16.33" size="1.27" layer="25" align="center">&gt;NAME</text>
<text x="2.225" y="-16.33" size="1.27" layer="27" align="center">&gt;VALUE</text>
<wire x1="-10.49" y1="3.04" x2="14.94" y2="3.04" width="0.1" layer="51"/>
<wire x1="14.94" y1="3.04" x2="14.94" y2="-7.15" width="0.1" layer="51"/>
<wire x1="14.94" y1="-7.15" x2="-10.49" y2="-7.15" width="0.1" layer="51"/>
<wire x1="-10.49" y1="-7.15" x2="-10.49" y2="3.04" width="0.1" layer="51"/>
<wire x1="-17.95" y1="4.8" x2="22.4" y2="4.8" width="0.1" layer="51"/>
<wire x1="22.4" y1="4.8" x2="22.4" y2="-37.46" width="0.1" layer="51"/>
<wire x1="22.4" y1="-37.46" x2="-17.95" y2="-37.46" width="0.1" layer="51"/>
<wire x1="-17.95" y1="-37.46" x2="-17.95" y2="4.8" width="0.1" layer="51"/>
<wire x1="-10.49" y1="-7.15" x2="-16.95" y2="-7.15" width="0.1" layer="51"/>
<wire x1="-16.95" y1="-7.15" x2="-16.95" y2="-21.85" width="0.1" layer="51"/>
<wire x1="-16.95" y1="-21.85" x2="21.4" y2="-21.85" width="0.1" layer="51"/>
<wire x1="21.4" y1="-21.85" x2="21.4" y2="-7.15" width="0.1" layer="51"/>
<wire x1="21.4" y1="-7.15" x2="14.94" y2="-7.15" width="0.1" layer="51"/>
<wire x1="-8.19" y1="-21.85" x2="-8.19" y2="-36.46" width="0.1" layer="51"/>
<wire x1="-8.19" y1="-36.46" x2="12.64" y2="-36.46" width="0.1" layer="51"/>
<wire x1="12.64" y1="-36.46" x2="12.64" y2="-21.85" width="0.1" layer="51"/>
<wire x1="-10.49" y1="-7.15" x2="-16.95" y2="-7.24" width="0.2" layer="21"/>
<wire x1="-16.95" y1="-7.24" x2="-16.95" y2="-21.85" width="0.2" layer="21"/>
<wire x1="-16.95" y1="-21.85" x2="21.4" y2="-21.85" width="0.2" layer="21"/>
<wire x1="21.4" y1="-21.85" x2="21.4" y2="-7.15" width="0.2" layer="21"/>
<wire x1="21.4" y1="-7.15" x2="14.94" y2="-7.15" width="0.2" layer="21"/>
<wire x1="-2.775" y1="-7.15" x2="-10.49" y2="-7.15" width="0.2" layer="21"/>
<wire x1="-10.49" y1="-7.15" x2="-10.49" y2="3.04" width="0.2" layer="21"/>
<wire x1="-10.49" y1="3.04" x2="14.94" y2="3.04" width="0.2" layer="21"/>
<wire x1="14.94" y1="3.04" x2="14.94" y2="-7.15" width="0.2" layer="21"/>
<wire x1="14.94" y1="-7.15" x2="7.225" y2="-7.15" width="0.2" layer="21"/>
<wire x1="0" y1="3.6" x2="0" y2="3.6" width="0.2" layer="21"/>
<wire x1="0" y1="3.6" x2="0" y2="3.8" width="0.2" layer="21" curve="180"/>
<wire x1="0" y1="3.8" x2="0" y2="3.8" width="0.2" layer="21"/>
<wire x1="0" y1="3.8" x2="0" y2="3.6" width="0.2" layer="21" curve="180"/>
</package>
</packages>
<symbols>
<symbol name="DT13-4P">
<wire x1="5.08" y1="2.54" x2="17.78" y2="2.54" width="0.254" layer="94"/>
<wire x1="17.78" y1="-10.16" x2="17.78" y2="2.54" width="0.254" layer="94"/>
<wire x1="17.78" y1="-10.16" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<wire x1="5.08" y1="2.54" x2="5.08" y2="-10.16" width="0.254" layer="94"/>
<text x="19.05" y="7.62" size="1.778" layer="95" align="center-left">&gt;NAME</text>
<text x="19.05" y="5.08" size="1.778" layer="96" align="center-left">&gt;VALUE</text>
<pin name="1" x="0" y="0" length="middle"/>
<pin name="2" x="0" y="-2.54" length="middle"/>
<pin name="3" x="0" y="-5.08" length="middle"/>
<pin name="4" x="0" y="-7.62" length="middle"/>
<pin name="MH1" x="22.86" y="0" length="middle" rot="R180"/>
<pin name="MH2" x="22.86" y="-2.54" length="middle" rot="R180"/>
<pin name="MH3" x="22.86" y="-5.08" length="middle" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="DT13-4P" prefix="J">
<description>&lt;b&gt;HDR, 4P, GRY, RA, NI/CU RECEPTACLE HEADER 4 PIN 90 DEG DT SERIES&lt;/b&gt;&lt;p&gt;
Source: &lt;a href="https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&amp;DocNm=DT13-4P&amp;DocType=Customer Drawing&amp;DocLang=English"&gt; Datasheet &lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="DT13-4P" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DT134P">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="MH1" pad="MH1"/>
<connect gate="G$1" pin="MH2" pad="MH2"/>
<connect gate="G$1" pin="MH3" pad="MH3"/>
</connects>
<technologies>
<technology name="">
<attribute name="DESCRIPTION" value="HDR, 4P, GRY, RA, NI/CU RECEPTACLE HEADER 4 PIN 90 DEG DT SERIES" constant="no"/>
<attribute name="HEIGHT" value="36.12mm" constant="no"/>
<attribute name="MANUFACTURER_NAME" value="TE Connectivity" constant="no"/>
<attribute name="MANUFACTURER_PART_NUMBER" value="DT13-4P" constant="no"/>
<attribute name="MOUSER_PART_NUMBER" value="571-DT13-4P" constant="no"/>
<attribute name="MOUSER_PRICE-STOCK" value="https://www.mouser.co.uk/ProductDetail/TE-Connectivity-DEUTSCH/DT13-4P?qs=vkMqrgFpRajaLeBfOZKzWQ%3D%3D" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="J1" library="DT13-4P" deviceset="DT13-4P" device=""/>
<part name="J2" library="DT13-4P" deviceset="DT13-4P" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="J1" gate="G$1" x="7.62" y="27.94" smashed="yes">
<attribute name="NAME" x="26.67" y="35.56" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="26.67" y="33.02" size="1.778" layer="96" align="center-left"/>
</instance>
<instance part="J2" gate="G$1" x="58.42" y="25.4" smashed="yes">
<attribute name="NAME" x="77.47" y="33.02" size="1.778" layer="95" align="center-left"/>
<attribute name="VALUE" x="77.47" y="30.48" size="1.778" layer="96" align="center-left"/>
</instance>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
