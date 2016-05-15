<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
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
<layer number="21" name="tPlace" color="16" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="14" fill="1" visible="no" active="no"/>
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
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="no" active="no"/>
<layer number="100" name="Muster" color="7" fill="1" visible="no" active="no"/>
<layer number="101" name="Patch_Top" color="12" fill="4" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="16" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="tplace-old" color="10" fill="1" visible="yes" active="yes"/>
<layer number="109" name="ref-old" color="11" fill="1" visible="yes" active="yes"/>
<layer number="110" name="fp0" color="7" fill="1" visible="yes" active="yes"/>
<layer number="111" name="LPC17xx" color="7" fill="1" visible="yes" active="yes"/>
<layer number="112" name="tSilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="113" name="IDFDebug" color="7" fill="1" visible="yes" active="yes"/>
<layer number="114" name="Badge_Outline" color="11" fill="1" visible="no" active="no"/>
<layer number="116" name="Patch_BOT" color="9" fill="4" visible="yes" active="yes"/>
<layer number="118" name="Rect_Pads" color="7" fill="1" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="123" name="tTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="124" name="bTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="126" name="_bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="127" name="_tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="128" name="_bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="129" name="Mask" color="7" fill="1" visible="yes" active="yes"/>
<layer number="131" name="tAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="132" name="bAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="150" name="Notes" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="152" name="_bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="153" name="FabDoc1" color="7" fill="1" visible="yes" active="yes"/>
<layer number="154" name="FabDoc2" color="7" fill="1" visible="yes" active="yes"/>
<layer number="155" name="FabDoc3" color="7" fill="1" visible="yes" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="1" fill="10" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="2" fill="10" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="3" fill="10" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="4" fill="10" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="5" fill="10" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="6" fill="10" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="10" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="8" fill="10" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="9" fill="10" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="18" fill="1" visible="no" active="no"/>
<layer number="218" name="218bmp" color="19" fill="1" visible="no" active="no"/>
<layer number="219" name="219bmp" color="20" fill="1" visible="no" active="no"/>
<layer number="220" name="220bmp" color="21" fill="1" visible="no" active="no"/>
<layer number="221" name="221bmp" color="22" fill="1" visible="no" active="no"/>
<layer number="222" name="222bmp" color="23" fill="1" visible="no" active="no"/>
<layer number="223" name="223bmp" color="24" fill="1" visible="no" active="no"/>
<layer number="224" name="224bmp" color="25" fill="1" visible="no" active="no"/>
<layer number="225" name="225bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="226" name="226bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="227" name="227bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="228" name="228bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="229" name="229bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="230" name="230bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="231" name="231bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="248" name="Housing" color="7" fill="1" visible="yes" active="yes"/>
<layer number="249" name="Edge" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="3" fill="1" visible="no" active="no"/>
<layer number="251" name="SMDround" color="12" fill="11" visible="no" active="no"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
<layer number="255" name="routoute" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="SparkFun-Boards">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find boards and modules: Arduino footprints, breadboards, non-RF modules, etc.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="LOGIC_LEVEL_CONVERTER">
<pad name="P$1" x="1.27" y="13.97" drill="0.8"/>
<pad name="P$2" x="1.27" y="11.43" drill="0.8"/>
<pad name="P$3" x="1.27" y="8.89" drill="0.8"/>
<pad name="P$4" x="1.27" y="6.35" drill="0.8"/>
<pad name="P$5" x="1.27" y="3.81" drill="0.8"/>
<pad name="P$6" x="1.27" y="1.27" drill="0.8"/>
<pad name="P$7" x="11.43" y="1.27" drill="0.8"/>
<pad name="P$8" x="11.43" y="3.81" drill="0.8"/>
<pad name="P$9" x="11.43" y="6.35" drill="0.8"/>
<pad name="P$10" x="11.43" y="8.89" drill="0.8"/>
<pad name="P$11" x="11.43" y="11.43" drill="0.8"/>
<pad name="P$12" x="11.43" y="13.97" drill="0.8"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.127" layer="21"/>
<wire x1="0" y1="5.08" x2="0" y2="10.16" width="0.127" layer="21"/>
<wire x1="0" y1="10.16" x2="0" y2="15.24" width="0.127" layer="21"/>
<wire x1="0" y1="15.24" x2="12.7" y2="15.24" width="0.127" layer="21"/>
<wire x1="12.7" y1="15.24" x2="12.7" y2="10.16" width="0.127" layer="21"/>
<wire x1="12.7" y1="10.16" x2="12.7" y2="5.08" width="0.127" layer="21"/>
<wire x1="12.7" y1="5.08" x2="12.7" y2="0" width="0.127" layer="21"/>
<wire x1="12.7" y1="0" x2="0" y2="0" width="0.127" layer="21"/>
<text x="3.81" y="10.16" size="1.27" layer="21">Chan1</text>
<text x="3.81" y="3.81" size="1.27" layer="21">Chan2</text>
<wire x1="0" y1="10.16" x2="12.7" y2="10.16" width="0.127" layer="21"/>
<wire x1="0" y1="5.08" x2="12.7" y2="5.08" width="0.127" layer="21"/>
<text x="2.54" y="13.97" size="1.27" layer="21">LV</text>
<text x="2.54" y="0" size="1.27" layer="21">LV</text>
<text x="7.62" y="13.97" size="1.27" layer="21">HV</text>
<text x="7.62" y="0" size="1.27" layer="21">HV</text>
</package>
</packages>
<symbols>
<symbol name="LOGIC_LEVEL_CONVERTER">
<description>Logic Level Converter (3.3v - 5v)</description>
<pin name="HV_TXO_1" x="7.62" y="30.48" length="middle" rot="R180"/>
<pin name="HV_RXI_1" x="7.62" y="27.94" length="middle" rot="R180"/>
<pin name="HV" x="7.62" y="25.4" length="middle" rot="R180"/>
<pin name="GND@2" x="7.62" y="22.86" length="middle" rot="R180"/>
<pin name="HV_RXI_2" x="7.62" y="20.32" length="middle" rot="R180"/>
<pin name="HV_TXO_2" x="7.62" y="17.78" length="middle" rot="R180"/>
<pin name="LV_TXI_1" x="-30.48" y="30.48" length="middle"/>
<pin name="LV" x="-30.48" y="25.4" length="middle"/>
<pin name="LV_RXO_1" x="-30.48" y="27.94" length="middle"/>
<pin name="GND" x="-30.48" y="22.86" length="middle"/>
<pin name="LV_RXO_2" x="-30.48" y="20.32" length="middle"/>
<pin name="LV_TXI_2" x="-30.48" y="17.78" length="middle"/>
<wire x1="-25.4" y1="15.24" x2="-25.4" y2="33.02" width="0.254" layer="94"/>
<wire x1="-25.4" y1="33.02" x2="2.54" y2="33.02" width="0.254" layer="94"/>
<wire x1="2.54" y1="33.02" x2="2.54" y2="15.24" width="0.254" layer="94"/>
<wire x1="2.54" y1="15.24" x2="-25.4" y2="15.24" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="LOGIC_LEVEL_CONVERTER">
<description>Logic Level Converter (3.3v - 5v)


https://www.sparkfun.com/products/8745</description>
<gates>
<gate name="G$1" symbol="LOGIC_LEVEL_CONVERTER" x="10.16" y="-22.86"/>
</gates>
<devices>
<device name="" package="LOGIC_LEVEL_CONVERTER">
<connects>
<connect gate="G$1" pin="GND" pad="P$4"/>
<connect gate="G$1" pin="GND@2" pad="P$9"/>
<connect gate="G$1" pin="HV" pad="P$10"/>
<connect gate="G$1" pin="HV_RXI_1" pad="P$11"/>
<connect gate="G$1" pin="HV_RXI_2" pad="P$8"/>
<connect gate="G$1" pin="HV_TXO_1" pad="P$12"/>
<connect gate="G$1" pin="HV_TXO_2" pad="P$7"/>
<connect gate="G$1" pin="LV" pad="P$3"/>
<connect gate="G$1" pin="LV_RXO_1" pad="P$2"/>
<connect gate="G$1" pin="LV_RXO_2" pad="P$5"/>
<connect gate="G$1" pin="LV_TXI_1" pad="P$1"/>
<connect gate="G$1" pin="LV_TXI_2" pad="P$6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-amp">
<description>&lt;b&gt;AMP Connectors&lt;/b&gt;&lt;p&gt;
RJ45 Jack connectors&lt;br&gt;
 Based on the previous libraris:
 &lt;ul&gt;
 &lt;li&gt;amp.lbr
 &lt;li&gt;amp-j.lbr
 &lt;li&gt;amp-mta.lbr
 &lt;li&gt;amp-nlok.lbr
 &lt;li&gt;amp-sim.lbr
 &lt;li&gt;amp-micro-match.lbr
 &lt;/ul&gt;
 Sources :
 &lt;ul&gt;
 &lt;li&gt;Catalog 82066 Revised 11-95 
 &lt;li&gt;Product Guide 296785 Rev. 8-99
 &lt;li&gt;Product Guide CD-ROM 1999
 &lt;li&gt;www.amp.com
 &lt;/ul&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="10X03MTA">
<description>&lt;b&gt;AMP MTA connector&lt;/b&gt;&lt;p&gt;
Source: http://ecommas.tycoelectronics.com .. ENG_CD_640456_W.pdf</description>
<wire x1="-3.81" y1="-1.27" x2="-3.81" y2="1.27" width="0.1524" layer="21"/>
<wire x1="3.81" y1="1.27" x2="-3.81" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="-1.27" x2="3.81" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="1.27" x2="-3.81" y2="1.905" width="0.1524" layer="21"/>
<wire x1="3.81" y1="1.905" x2="-3.81" y2="1.905" width="0.1524" layer="21"/>
<wire x1="3.81" y1="1.27" x2="3.81" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.81" y1="1.905" x2="3.81" y2="1.27" width="0.1524" layer="21"/>
<pad name="3" x="-2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="0" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="1" x="2.54" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-2.6162" y="-3.2512" size="1.27" layer="25">&gt;NAME</text>
<text x="-3.7762" y="2.1509" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="21"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="21"/>
<rectangle x1="-2.794" y1="-0.254" x2="-2.286" y2="0.254" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="MTA-1_3">
<wire x1="-3.81" y1="1.27" x2="-3.81" y2="-1.905" width="0.254" layer="94"/>
<wire x1="3.81" y1="-1.905" x2="-3.81" y2="-1.905" width="0.254" layer="94"/>
<wire x1="3.81" y1="-1.905" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<wire x1="-3.81" y1="1.27" x2="3.81" y2="1.27" width="0.254" layer="94"/>
<circle x="-2.54" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="0" y="0" radius="0.635" width="0.254" layer="94"/>
<circle x="2.54" y="0" radius="0.635" width="0.254" layer="94"/>
<text x="5.08" y="0" size="1.778" layer="95">&gt;NAME</text>
<text x="5.08" y="-3.81" size="1.778" layer="96">&gt;VALUE</text>
<text x="-5.08" y="-1.27" size="1.27" layer="95">1</text>
<pin name="1" x="-2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="3" x="2.54" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
<pin name="2" x="0" y="-2.54" visible="off" length="short" direction="pas" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MTA03-100" prefix="J" uservalue="yes">
<description>&lt;b&gt;AMP connector&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="MTA-1_3" x="0" y="0"/>
</gates>
<devices>
<device name="" package="10X03MTA">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="esp8266modules">
<packages>
<package name="ESP01">
<description>ESP8266 Module 01</description>
<pad name="GND" x="-3.825" y="-5.6375" drill="0.8" shape="square" rot="R270"/>
<pad name="RX" x="3.795" y="-5.6375" drill="0.8" shape="square" rot="R270"/>
<pad name="GPIO2" x="-1.285" y="-5.6375" drill="0.8" rot="R270"/>
<pad name="GPIO0" x="1.255" y="-5.6375" drill="0.8" rot="R270"/>
<pad name="RST" x="1.255" y="-8.1775" drill="0.8" rot="R270"/>
<pad name="CH_PD" x="-1.285" y="-8.1775" drill="0.8" rot="R270"/>
<pad name="TX" x="-3.825" y="-8.1775" drill="0.8" rot="R270"/>
<pad name="VCC" x="3.795" y="-8.1775" drill="0.8" rot="R270"/>
<wire x1="-7" y1="15" x2="-7" y2="7.38" width="0.127" layer="21"/>
<wire x1="-7" y1="7.38" x2="-7" y2="-9.765" width="0.127" layer="21"/>
<wire x1="-7" y1="-9.765" x2="7.2875" y2="-9.765" width="0.127" layer="21"/>
<wire x1="7.2875" y1="-9.765" x2="7.2875" y2="7.38" width="0.127" layer="21"/>
<wire x1="7.2875" y1="7.38" x2="7.2875" y2="15" width="0.127" layer="21"/>
<wire x1="7.2875" y1="15" x2="-7" y2="15" width="0.127" layer="21"/>
<wire x1="-7" y1="7.38" x2="7.2875" y2="7.38" width="0.127" layer="21"/>
<text x="-5.73" y="9.92" size="2.54" layer="21">ESP-01</text>
<text x="-7" y="16" size="1.27" layer="25">&gt;Name</text>
<text x="-7" y="-11" size="1.27" layer="27">&gt;Value</text>
</package>
</packages>
<symbols>
<symbol name="ESP01">
<description>ESP8266 Wifi module 01</description>
<wire x1="-12.7" y1="10.16" x2="-12.7" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-12.7" y1="-2.54" x2="10.16" y2="-2.54" width="0.254" layer="94"/>
<wire x1="10.16" y1="-2.54" x2="10.16" y2="10.16" width="0.254" layer="94"/>
<wire x1="10.16" y1="10.16" x2="-12.7" y2="10.16" width="0.254" layer="94"/>
<pin name="GND" x="-17.78" y="7.62" visible="pin" length="middle"/>
<pin name="GPIO2" x="-17.78" y="5.08" visible="pin" length="middle"/>
<pin name="GPIO0" x="-17.78" y="2.54" visible="pin" length="middle"/>
<pin name="RXD" x="-17.78" y="0" visible="pin" length="middle"/>
<pin name="TXD" x="15.24" y="7.62" visible="pin" length="middle" rot="R180"/>
<pin name="CH_PD" x="15.24" y="5.08" visible="pin" length="middle" rot="R180"/>
<pin name="RST" x="15.24" y="2.54" visible="pin" length="middle" rot="R180"/>
<pin name="VCC" x="15.24" y="0" visible="pin" length="middle" rot="R180"/>
<text x="-12.7" y="10.16" size="1.778" layer="95">&gt;Name</text>
<text x="-12.7" y="-5.08" size="1.778" layer="95">&gt;Value</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP01">
<description>ESP8266 Wifi module 01</description>
<gates>
<gate name="G$1" symbol="ESP01" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ESP01">
<connects>
<connect gate="G$1" pin="CH_PD" pad="CH_PD"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GPIO0" pad="GPIO0"/>
<connect gate="G$1" pin="GPIO2" pad="GPIO2"/>
<connect gate="G$1" pin="RST" pad="RST"/>
<connect gate="G$1" pin="RXD" pad="RX"/>
<connect gate="G$1" pin="TXD" pad="TX"/>
<connect gate="G$1" pin="VCC" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-ptr500">
<description>&lt;b&gt;PTR Connectors&lt;/b&gt;&lt;p&gt;
Aug. 2004 / PTR Meßtechnik:&lt;br&gt;
Die Bezeichnung der Serie AK505 wurde geändert.&lt;br&gt;
Es handelt sich hierbei um AK500 in horizontaler Ausführung.&lt;p&gt;
&lt;TABLE BORDER=0 CELLSPACING=1 CELLPADDING=2&gt;
  &lt;TR&gt;
    &lt;TD ALIGN=LEFT&gt;
      &lt;FONT SIZE=4 FACE=ARIAL&gt;&lt;B&gt;Alte Bezeichnung&lt;/B&gt;&lt;/FONT&gt;
    &lt;/TD&gt;
    &lt;TD ALIGN=LEFT&gt;
      &lt;FONT SIZE=4 FACE=ARIAL&gt;&lt;B&gt;Neue Bezeichnung&lt;/B&gt;&lt;/FONT&gt;
    &lt;/TD&gt;
  &lt;/TR&gt;
  &lt;TR&gt;
    &lt;TD ALIGN=LEFT&gt;
      &lt;B&gt;
      &lt;FONT SIZE=3 FACE=ARIAL color="#FF0000"&gt;AK505/2,grau&lt;/FONT&gt;
      &lt;/B&gt;
    &lt;/TD&gt;
    &lt;TD ALIGN=LEFT&gt;
      &lt;B&gt;
      &lt;FONT SIZE=3 FACE=ARIAL color="#0000FF"&gt;AK500/2-5.0-H-GRAU&lt;/FONT&gt;
      &lt;/B&gt;
    &lt;/TD&gt;
  &lt;/TR&gt;
  &lt;TR&gt;
    &lt;TD ALIGN=LEFT&gt;
      &lt;B&gt;
      &lt;FONT SIZE=3 FACE=ARIAL color="#FF0000"&gt;AK505/2DS,grau&lt;/FONT&gt;
      &lt;/B&gt;
    &lt;/TD&gt;
    &lt;TD ALIGN=LEFT&gt;
      &lt;B&gt;
      &lt;FONT SIZE=3 FACE=ARIAL color="#0000FF"&gt;AK500/2DS-5.0-H-GRAU&lt;/FONT&gt;
      &lt;/B&gt;
    &lt;/TD&gt;
  &lt;/TR&gt;
  &lt;TR&gt;
    &lt;TD ALIGN=LEFT&gt;
      &lt;B&gt;
      &lt;FONT SIZE=3 FACE=ARIAL color="#FF0000"&gt;AKZ505/2,grau&lt;/FONT&gt;
      &lt;/B&gt;
    &lt;/TD&gt;
    &lt;TD ALIGN=LEFT&gt;
      &lt;B&gt;
      &lt;FONT SIZE=3 FACE=ARIAL color="#0000FF"&gt;AKZ500/2-5.08-H-GRAU&lt;/FONT&gt;
      &lt;/B&gt;
    &lt;/TD&gt;
  &lt;/TABLE&gt;

&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="AK300/2">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;</description>
<wire x1="5.08" y1="6.223" x2="5.08" y2="3.175" width="0.1524" layer="21"/>
<wire x1="5.08" y1="6.223" x2="-5.08" y2="6.223" width="0.1524" layer="21"/>
<wire x1="5.08" y1="6.223" x2="5.588" y2="6.223" width="0.1524" layer="21"/>
<wire x1="5.588" y1="6.223" x2="5.588" y2="1.397" width="0.1524" layer="21"/>
<wire x1="5.588" y1="1.397" x2="5.08" y2="1.651" width="0.1524" layer="21"/>
<wire x1="5.588" y1="-5.461" x2="5.08" y2="-5.207" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-5.207" x2="5.08" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="5.588" y1="-3.81" x2="5.08" y2="-4.064" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-4.064" x2="5.08" y2="-5.207" width="0.1524" layer="21"/>
<wire x1="5.588" y1="-3.81" x2="5.588" y2="-5.461" width="0.1524" layer="21"/>
<wire x1="0.4572" y1="-6.223" x2="0.4572" y2="-4.318" width="0.1524" layer="21"/>
<wire x1="4.5212" y1="0.254" x2="4.5212" y2="-4.318" width="0.1524" layer="21"/>
<wire x1="0.4572" y1="-6.223" x2="4.5212" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="4.5212" y1="-6.223" x2="5.08" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-0.4826" y1="-6.223" x2="-0.4826" y2="-4.318" width="0.1524" layer="21"/>
<wire x1="-0.4826" y1="-6.223" x2="0.4572" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-4.5466" y1="0.254" x2="-4.5466" y2="-4.318" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-6.223" x2="-4.5466" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-4.5466" y1="-6.223" x2="-0.4826" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="0.4572" y1="-4.318" x2="4.5212" y2="-4.318" width="0.1524" layer="21"/>
<wire x1="0.4572" y1="-4.318" x2="0.4572" y2="0.254" width="0.1524" layer="21"/>
<wire x1="4.5212" y1="-4.318" x2="4.5212" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="-0.4826" y1="-4.318" x2="-4.5466" y2="-4.318" width="0.1524" layer="21"/>
<wire x1="-0.4826" y1="-4.318" x2="-0.4826" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-4.5466" y1="-4.318" x2="-4.5466" y2="-6.223" width="0.1524" layer="21"/>
<wire x1="4.1402" y1="-3.683" x2="4.1402" y2="-0.508" width="0.1524" layer="21"/>
<wire x1="4.1402" y1="-3.683" x2="0.8382" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="0.8382" y1="-3.683" x2="0.8382" y2="-0.508" width="0.1524" layer="21"/>
<wire x1="-0.8636" y1="-3.683" x2="-0.8636" y2="-0.508" width="0.1524" layer="21"/>
<wire x1="-0.8636" y1="-3.683" x2="-4.1656" y2="-3.683" width="0.1524" layer="21"/>
<wire x1="-4.1656" y1="-3.683" x2="-4.1656" y2="-0.508" width="0.1524" layer="21"/>
<wire x1="-4.1656" y1="-0.508" x2="-3.7846" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="-0.508" x2="-1.2446" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="0.8382" y1="-0.508" x2="1.2192" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="4.1402" y1="-0.508" x2="3.7592" y2="-0.508" width="0.1524" layer="51"/>
<wire x1="-5.08" y1="-6.223" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="3.175" width="0.1524" layer="21"/>
<wire x1="5.08" y1="1.651" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.08" y2="-4.064" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="3.175" x2="5.08" y2="3.175" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="3.175" x2="-5.08" y2="6.223" width="0.1524" layer="21"/>
<wire x1="5.08" y1="3.175" x2="5.08" y2="1.651" width="0.1524" layer="21"/>
<wire x1="0.4572" y1="3.429" x2="0.4572" y2="5.969" width="0.1524" layer="21"/>
<wire x1="0.4572" y1="5.969" x2="4.5212" y2="5.969" width="0.1524" layer="21"/>
<wire x1="4.5212" y1="5.969" x2="4.5212" y2="3.429" width="0.1524" layer="21"/>
<wire x1="4.5212" y1="3.429" x2="0.4572" y2="3.429" width="0.1524" layer="21"/>
<wire x1="-0.4826" y1="3.429" x2="-0.4826" y2="5.969" width="0.1524" layer="21"/>
<wire x1="-0.4826" y1="3.429" x2="-4.5466" y2="3.429" width="0.1524" layer="21"/>
<wire x1="-4.5466" y1="3.429" x2="-4.5466" y2="5.969" width="0.1524" layer="21"/>
<wire x1="-0.4826" y1="5.969" x2="-4.5466" y2="5.969" width="0.1524" layer="21"/>
<wire x1="3.9574" y1="4.0849" x2="4.0131" y2="5.0545" width="0.1524" layer="21" curve="90.564135"/>
<wire x1="1.016" y1="4.1656" x2="4.0038" y2="4.1189" width="0.1524" layer="21" curve="75.530157"/>
<wire x1="0.8636" y1="5.0038" x2="4.0178" y2="5.0586" width="0.1524" layer="21" curve="-100.0232"/>
<wire x1="0.9144" y1="5.0546" x2="1.0581" y2="4.1297" width="0.1524" layer="21" curve="104.208873"/>
<wire x1="0.8636" y1="4.445" x2="3.9116" y2="5.08" width="0.1524" layer="21"/>
<wire x1="0.9906" y1="4.318" x2="4.0386" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-1.0464" y1="4.0849" x2="-0.9907" y2="5.0545" width="0.1524" layer="21" curve="90.564135"/>
<wire x1="-3.9878" y1="4.1656" x2="-1" y2="4.1188" width="0.1524" layer="21" curve="75.528719"/>
<wire x1="-4.1402" y1="5.0038" x2="-0.9858" y2="5.0588" width="0.1524" layer="21" curve="-100.022513"/>
<wire x1="-4.0894" y1="5.0546" x2="-3.9457" y2="4.1297" width="0.1524" layer="21" curve="104.208873"/>
<wire x1="-4.1402" y1="4.445" x2="-1.0922" y2="5.08" width="0.1524" layer="21"/>
<wire x1="-4.0132" y1="4.318" x2="-0.9652" y2="4.953" width="0.1524" layer="21"/>
<wire x1="-4.5466" y1="0.254" x2="-4.1656" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-0.4826" y1="0.254" x2="-0.8636" y2="0.254" width="0.1524" layer="21"/>
<wire x1="-0.8636" y1="0.254" x2="-4.1656" y2="0.254" width="0.1524" layer="51"/>
<wire x1="-5.08" y1="0.635" x2="-4.1656" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-4.1656" y1="0.635" x2="-0.8636" y2="0.635" width="0.1524" layer="51"/>
<wire x1="-0.8636" y1="0.635" x2="0.8382" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="4.1402" y2="0.635" width="0.1524" layer="21"/>
<wire x1="4.1402" y1="0.635" x2="0.8382" y2="0.635" width="0.1524" layer="51"/>
<wire x1="4.5212" y1="0.254" x2="4.1402" y2="0.254" width="0.1524" layer="21"/>
<wire x1="0.4572" y1="0.254" x2="0.8382" y2="0.254" width="0.1524" layer="21"/>
<wire x1="0.8382" y1="0.254" x2="4.1402" y2="0.254" width="0.1524" layer="51"/>
<pad name="1" x="-2.5146" y="0" drill="1.3208" shape="long" rot="R90"/>
<pad name="2" x="2.4892" y="0" drill="1.3208" shape="long" rot="R90"/>
<text x="-5.08" y="6.731" size="1.778" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-8.636" size="1.778" layer="27" ratio="10">&gt;VALUE</text>
<text x="-4.4958" y="1.27" size="1.27" layer="21" ratio="10">1</text>
<text x="0.5842" y="1.27" size="1.27" layer="21" ratio="10">2</text>
<rectangle x1="-3.7846" y1="-2.54" x2="-1.2446" y2="0.254" layer="51"/>
<rectangle x1="1.2192" y1="-2.54" x2="3.7592" y2="0.254" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="KL">
<circle x="1.27" y="0" radius="1.27" width="0.254" layer="94"/>
<text x="-1.27" y="0.889" size="1.778" layer="95" rot="R180">&gt;NAME</text>
<pin name="KL" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
<symbol name="KLV">
<circle x="1.27" y="0" radius="1.27" width="0.254" layer="94"/>
<text x="-1.27" y="0.889" size="1.778" layer="95" rot="R180">&gt;NAME</text>
<text x="-3.81" y="-3.683" size="1.778" layer="96">&gt;VALUE</text>
<pin name="KL" x="5.08" y="0" visible="off" length="short" direction="pas" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="AK300/2" prefix="X" uservalue="yes">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;</description>
<gates>
<gate name="-1" symbol="KL" x="0" y="5.08" addlevel="always"/>
<gate name="-2" symbol="KLV" x="0" y="0" addlevel="always"/>
</gates>
<devices>
<device name="" package="AK300/2">
<connects>
<connect gate="-1" pin="KL" pad="1"/>
<connect gate="-2" pin="KL" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-1.905" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="GND" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="VCC">
<wire x1="1.27" y1="-1.905" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="-1.27" y2="-1.905" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96" rot="R90">&gt;VALUE</text>
<pin name="VCC" x="0" y="-2.54" visible="off" length="short" direction="sup" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="VCC" prefix="P+">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="VCC" symbol="VCC" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="STM32F4-DISCOVERY_CF_INTECH">
<packages>
<package name="STM32F4-DISCOVERY">
<wire x1="-33.02" y1="-48.26" x2="33.02" y2="-48.26" width="0.127" layer="21"/>
<wire x1="33.02" y1="-48.26" x2="33.02" y2="48.26" width="0.127" layer="21"/>
<wire x1="33.02" y1="48.26" x2="3.81" y2="48.26" width="0.127" layer="21"/>
<wire x1="3.81" y1="48.26" x2="-3.81" y2="48.26" width="0.127" layer="21"/>
<wire x1="-3.81" y1="48.26" x2="-33.02" y2="48.26" width="0.127" layer="21"/>
<wire x1="-33.02" y1="48.26" x2="-33.02" y2="-48.26" width="0.127" layer="21"/>
<pad name="GND" x="-26.67" y="15.24" drill="0.8" shape="square"/>
<pad name="GND1" x="-24.13" y="15.24" drill="0.8"/>
<pad name="VDD" x="-26.67" y="12.7" drill="0.8"/>
<pad name="VDD1" x="-24.13" y="12.7" drill="0.8"/>
<pad name="GND2" x="-26.67" y="10.16" drill="0.8"/>
<pad name="NRST" x="-24.13" y="10.16" drill="0.8"/>
<pad name="PC1" x="-26.67" y="7.62" drill="0.8"/>
<pad name="PC0" x="-24.13" y="7.62" drill="0.8"/>
<pad name="PC3" x="-26.67" y="5.08" drill="0.8"/>
<pad name="PC2" x="-24.13" y="5.08" drill="0.8"/>
<pad name="PA1" x="-26.67" y="2.54" drill="0.8"/>
<pad name="PA0" x="-24.13" y="2.54" drill="0.8"/>
<pad name="PA3" x="-26.67" y="0" drill="0.8"/>
<pad name="PA2" x="-24.13" y="0" drill="0.8"/>
<pad name="PA5" x="-26.67" y="-2.54" drill="0.8"/>
<pad name="PA4" x="-24.13" y="-2.54" drill="0.8"/>
<pad name="PA7" x="-26.67" y="-5.08" drill="0.8"/>
<pad name="PA6" x="-24.13" y="-5.08" drill="0.8"/>
<pad name="PC5" x="-26.67" y="-7.62" drill="0.8"/>
<pad name="PC4" x="-24.13" y="-7.62" drill="0.8"/>
<pad name="PB1" x="-26.67" y="-10.16" drill="0.8"/>
<pad name="PB0" x="-24.13" y="-10.16" drill="0.8"/>
<pad name="GND3" x="-26.67" y="-12.7" drill="0.8"/>
<pad name="PB2" x="-24.13" y="-12.7" drill="0.8"/>
<pad name="PE7" x="-26.67" y="-15.24" drill="0.8"/>
<pad name="PE8" x="-24.13" y="-15.24" drill="0.8"/>
<pad name="PE9" x="-26.67" y="-17.78" drill="0.8"/>
<pad name="PE10" x="-24.13" y="-17.78" drill="0.8"/>
<pad name="PE11" x="-26.67" y="-20.32" drill="0.8"/>
<pad name="PE12" x="-24.13" y="-20.32" drill="0.8"/>
<pad name="PE13" x="-26.67" y="-22.86" drill="0.8"/>
<pad name="PE14" x="-24.13" y="-22.86" drill="0.8"/>
<pad name="PE15" x="-26.67" y="-25.4" drill="0.8"/>
<pad name="PB10" x="-24.13" y="-25.4" drill="0.8"/>
<pad name="PB11" x="-26.67" y="-27.94" drill="0.8"/>
<pad name="PB12" x="-24.13" y="-27.94" drill="0.8"/>
<pad name="PB13" x="-26.67" y="-30.48" drill="0.8"/>
<pad name="PB14" x="-24.13" y="-30.48" drill="0.8"/>
<pad name="PB15" x="-26.67" y="-33.02" drill="0.8"/>
<pad name="PD8" x="-24.13" y="-33.02" drill="0.8"/>
<pad name="PD9" x="-26.67" y="-35.56" drill="0.8"/>
<pad name="PD10" x="-24.13" y="-35.56" drill="0.8"/>
<pad name="PD11" x="-26.67" y="-38.1" drill="0.8"/>
<pad name="PD12" x="-24.13" y="-38.1" drill="0.8"/>
<pad name="PD13" x="-26.67" y="-40.64" drill="0.8"/>
<pad name="PD14" x="-24.13" y="-40.64" drill="0.8"/>
<pad name="PD15" x="-26.67" y="-43.18" drill="0.8"/>
<pad name="NC" x="-24.13" y="-43.18" drill="0.8"/>
<pad name="GND4" x="-26.67" y="-45.72" drill="0.8"/>
<pad name="GND5" x="-24.13" y="-45.72" drill="0.8"/>
<pad name="GND6" x="24.13" y="15.24" drill="0.8" shape="square"/>
<pad name="GND7" x="26.67" y="15.24" drill="0.8"/>
<pad name="5V" x="24.13" y="12.7" drill="0.8"/>
<pad name="5V2" x="26.67" y="12.7" drill="0.8"/>
<pad name="VDD2" x="24.13" y="10.16" drill="0.8"/>
<pad name="VDD3" x="26.67" y="10.16" drill="0.8"/>
<pad name="PH0" x="24.13" y="7.62" drill="0.8"/>
<pad name="PH1" x="26.67" y="7.62" drill="0.8"/>
<pad name="PC14" x="24.13" y="5.08" drill="0.8"/>
<pad name="PC15" x="26.67" y="5.08" drill="0.8"/>
<pad name="PE6" x="24.13" y="2.54" drill="0.8"/>
<pad name="PC13" x="26.67" y="2.54" drill="0.8"/>
<pad name="PE4" x="24.13" y="0" drill="0.8"/>
<pad name="PE5" x="26.67" y="0" drill="0.8"/>
<pad name="PE2" x="24.13" y="-2.54" drill="0.8"/>
<pad name="PE3" x="26.67" y="-2.54" drill="0.8"/>
<pad name="PE0" x="24.13" y="-5.08" drill="0.8"/>
<pad name="PE1" x="26.67" y="-5.08" drill="0.8"/>
<pad name="PB8" x="24.13" y="-7.62" drill="0.8"/>
<pad name="PB9" x="26.67" y="-7.62" drill="0.8"/>
<pad name="BOOT0" x="24.13" y="-10.16" drill="0.8"/>
<pad name="VDD4" x="26.67" y="-10.16" drill="0.8"/>
<pad name="PB6" x="24.13" y="-12.7" drill="0.8"/>
<pad name="PB7" x="26.67" y="-12.7" drill="0.8"/>
<pad name="PB4" x="24.13" y="-15.24" drill="0.8"/>
<pad name="PB5" x="26.67" y="-15.24" drill="0.8"/>
<pad name="PD7" x="24.13" y="-17.78" drill="0.8"/>
<pad name="PB3" x="26.67" y="-17.78" drill="0.8"/>
<pad name="PD5" x="24.13" y="-20.32" drill="0.8"/>
<pad name="PD6" x="26.67" y="-20.32" drill="0.8"/>
<pad name="PD3" x="24.13" y="-22.86" drill="0.8"/>
<pad name="PD4" x="26.67" y="-22.86" drill="0.8"/>
<pad name="PD1" x="24.13" y="-25.4" drill="0.8"/>
<pad name="PD2" x="26.67" y="-25.4" drill="0.8"/>
<pad name="PC12" x="24.13" y="-27.94" drill="0.8"/>
<pad name="PD0" x="26.67" y="-27.94" drill="0.8"/>
<pad name="PC10" x="24.13" y="-30.48" drill="0.8"/>
<pad name="PC11" x="26.67" y="-30.48" drill="0.8"/>
<pad name="PA14" x="24.13" y="-33.02" drill="0.8"/>
<pad name="PA15" x="26.67" y="-33.02" drill="0.8"/>
<pad name="PA10" x="24.13" y="-35.56" drill="0.8"/>
<pad name="PA13" x="26.67" y="-35.56" drill="0.8"/>
<pad name="PA8" x="24.13" y="-38.1" drill="0.8"/>
<pad name="PA9" x="26.67" y="-38.1" drill="0.8"/>
<pad name="PC8" x="24.13" y="-40.64" drill="0.8"/>
<pad name="PC9" x="26.67" y="-40.64" drill="0.8"/>
<pad name="PC6" x="24.13" y="-43.18" drill="0.8"/>
<pad name="PC7" x="26.67" y="-43.18" drill="0.8"/>
<pad name="GND8" x="24.13" y="-45.72" drill="0.8"/>
<pad name="GND9" x="26.67" y="-45.72" drill="0.8"/>
<wire x1="3.81" y1="48.26" x2="3.81" y2="39.37" width="0.127" layer="21"/>
<wire x1="3.81" y1="39.37" x2="-3.81" y2="39.37" width="0.127" layer="21"/>
<wire x1="-3.81" y1="39.37" x2="-3.81" y2="48.26" width="0.127" layer="21"/>
<wire x1="-3.81" y1="48.26" x2="-3.81" y2="49.53" width="0.127" layer="21"/>
<wire x1="3.81" y1="48.26" x2="3.81" y2="49.53" width="0.127" layer="21"/>
<wire x1="3.81" y1="49.53" x2="-3.81" y2="49.53" width="0.127" layer="21"/>
<wire x1="-2.54" y1="43.18" x2="-2.54" y2="46.99" width="0.127" layer="21"/>
<wire x1="-2.54" y1="46.99" x2="-1.27" y2="46.99" width="0.127" layer="21"/>
<wire x1="-1.27" y1="46.99" x2="-1.27" y2="43.18" width="0.127" layer="21"/>
<wire x1="2.54" y1="43.18" x2="2.54" y2="46.99" width="0.127" layer="21"/>
<wire x1="2.54" y1="46.99" x2="1.27" y2="46.99" width="0.127" layer="21"/>
<wire x1="1.27" y1="46.99" x2="1.27" y2="43.18" width="0.127" layer="21"/>
<wire x1="-2.54" y1="40.64" x2="-1.27" y2="40.64" width="0.127" layer="21"/>
<wire x1="-1.27" y1="40.64" x2="-1.27" y2="41.91" width="0.127" layer="21"/>
<wire x1="-1.27" y1="41.91" x2="1.27" y2="41.91" width="0.127" layer="21"/>
<wire x1="1.27" y1="41.91" x2="1.27" y2="40.64" width="0.127" layer="21"/>
<wire x1="1.27" y1="40.64" x2="2.54" y2="40.64" width="0.127" layer="21"/>
<text x="-2.54" y="36.83" size="1.778" layer="21">USB</text>
<text x="-29.21" y="24.13" size="2.54" layer="21">STM32F4 DISCOVERY @ INTech</text>
</package>
</packages>
<symbols>
<symbol name="STM32F4-DISCOVERY">
<wire x1="0" y1="-63.5" x2="0" y2="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="20.32" y2="2.54" width="0.254" layer="94"/>
<wire x1="20.32" y1="2.54" x2="20.32" y2="-63.5" width="0.254" layer="94"/>
<wire x1="20.32" y1="-63.5" x2="0" y2="-63.5" width="0.254" layer="94"/>
<wire x1="86.36" y1="-63.5" x2="86.36" y2="2.54" width="0.254" layer="94"/>
<wire x1="86.36" y1="2.54" x2="106.68" y2="2.54" width="0.254" layer="94"/>
<wire x1="106.68" y1="2.54" x2="106.68" y2="-63.5" width="0.254" layer="94"/>
<wire x1="106.68" y1="-63.5" x2="86.36" y2="-63.5" width="0.254" layer="94"/>
<wire x1="48.26" y1="10.16" x2="55.88" y2="10.16" width="0.254" layer="94"/>
<wire x1="55.88" y1="10.16" x2="55.88" y2="12.7" width="0.254" layer="94"/>
<wire x1="55.88" y1="15.24" x2="55.88" y2="17.78" width="0.254" layer="94"/>
<wire x1="55.88" y1="17.78" x2="55.88" y2="20.32" width="0.254" layer="94"/>
<wire x1="55.88" y1="20.32" x2="48.26" y2="20.32" width="0.254" layer="94"/>
<wire x1="48.26" y1="20.32" x2="48.26" y2="17.78" width="0.254" layer="94"/>
<wire x1="48.26" y1="17.78" x2="48.26" y2="15.24" width="0.254" layer="94"/>
<wire x1="48.26" y1="15.24" x2="48.26" y2="12.7" width="0.254" layer="94"/>
<wire x1="48.26" y1="12.7" x2="48.26" y2="10.16" width="0.254" layer="94"/>
<wire x1="48.26" y1="12.7" x2="45.72" y2="12.7" width="0.254" layer="94"/>
<wire x1="45.72" y1="12.7" x2="45.72" y2="10.16" width="0.254" layer="94"/>
<wire x1="45.72" y1="10.16" x2="48.26" y2="10.16" width="0.254" layer="94"/>
<wire x1="55.88" y1="10.16" x2="58.42" y2="10.16" width="0.254" layer="94"/>
<wire x1="58.42" y1="10.16" x2="58.42" y2="12.7" width="0.254" layer="94"/>
<wire x1="58.42" y1="12.7" x2="55.88" y2="12.7" width="0.254" layer="94"/>
<wire x1="55.88" y1="12.7" x2="55.88" y2="15.24" width="0.254" layer="94"/>
<wire x1="55.88" y1="15.24" x2="58.42" y2="15.24" width="0.254" layer="94"/>
<wire x1="58.42" y1="15.24" x2="58.42" y2="17.78" width="0.254" layer="94"/>
<wire x1="58.42" y1="17.78" x2="55.88" y2="17.78" width="0.254" layer="94"/>
<wire x1="48.26" y1="15.24" x2="45.72" y2="15.24" width="0.254" layer="94"/>
<wire x1="45.72" y1="15.24" x2="45.72" y2="17.78" width="0.254" layer="94"/>
<wire x1="45.72" y1="17.78" x2="48.26" y2="17.78" width="0.254" layer="94"/>
<text x="12.7" y="22.86" size="3.81" layer="94">STM32F4-DISCOVERY @ INTech</text>
<text x="49.276" y="13.716" size="1.9304" layer="94">USB</text>
<pin name="GND" x="-5.08" y="0" length="middle"/>
<pin name="VDD" x="-5.08" y="-2.54" length="middle"/>
<pin name="VDD1" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="NRST" x="25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="PC1" x="-5.08" y="-7.62" length="middle"/>
<pin name="PC0" x="25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="PC3" x="-5.08" y="-10.16" length="middle"/>
<pin name="PC2" x="25.4" y="-10.16" length="middle" rot="R180"/>
<pin name="PA1" x="-5.08" y="-12.7" length="middle"/>
<pin name="PA0" x="25.4" y="-12.7" length="middle" rot="R180"/>
<pin name="PA3" x="-5.08" y="-15.24" length="middle"/>
<pin name="PA2" x="25.4" y="-15.24" length="middle" rot="R180"/>
<pin name="PA5" x="-5.08" y="-17.78" length="middle"/>
<pin name="PA4" x="25.4" y="-17.78" length="middle" rot="R180"/>
<pin name="PA7" x="-5.08" y="-20.32" length="middle"/>
<pin name="PA6" x="25.4" y="-20.32" length="middle" rot="R180"/>
<pin name="PC5" x="-5.08" y="-22.86" length="middle"/>
<pin name="PC4" x="25.4" y="-22.86" length="middle" rot="R180"/>
<pin name="PB1" x="-5.08" y="-25.4" length="middle"/>
<pin name="PB0" x="25.4" y="-25.4" length="middle" rot="R180"/>
<pin name="GND3" x="-5.08" y="-27.94" length="middle"/>
<pin name="PB2" x="25.4" y="-27.94" length="middle" rot="R180"/>
<pin name="PE7" x="-5.08" y="-30.48" length="middle"/>
<pin name="PE8" x="25.4" y="-30.48" length="middle" rot="R180"/>
<pin name="PE9" x="-5.08" y="-33.02" length="middle"/>
<pin name="PE10" x="25.4" y="-33.02" length="middle" rot="R180"/>
<pin name="PE11" x="-5.08" y="-35.56" length="middle"/>
<pin name="PE12" x="25.4" y="-35.56" length="middle" rot="R180"/>
<pin name="PE13" x="-5.08" y="-38.1" length="middle"/>
<pin name="PE14" x="25.4" y="-38.1" length="middle" rot="R180"/>
<pin name="PE15" x="-5.08" y="-40.64" length="middle"/>
<pin name="PB10" x="25.4" y="-40.64" length="middle" rot="R180"/>
<pin name="PB11" x="-5.08" y="-43.18" length="middle"/>
<pin name="PB12" x="25.4" y="-43.18" length="middle" rot="R180"/>
<pin name="PB13" x="-5.08" y="-45.72" length="middle"/>
<pin name="PB14" x="25.4" y="-45.72" length="middle" rot="R180"/>
<pin name="PB15" x="-5.08" y="-48.26" length="middle"/>
<pin name="PD8" x="25.4" y="-48.26" length="middle" rot="R180"/>
<pin name="PD9" x="-5.08" y="-50.8" length="middle"/>
<pin name="PD10" x="25.4" y="-50.8" length="middle" rot="R180"/>
<pin name="PD11" x="-5.08" y="-53.34" length="middle"/>
<pin name="PD12" x="25.4" y="-53.34" length="middle" rot="R180"/>
<pin name="PD13" x="-5.08" y="-55.88" length="middle"/>
<pin name="PD14" x="25.4" y="-55.88" length="middle" rot="R180"/>
<pin name="PD15" x="-5.08" y="-58.42" length="middle"/>
<pin name="NC" x="25.4" y="-58.42" length="middle" rot="R180"/>
<pin name="GND4" x="-5.08" y="-60.96" length="middle"/>
<pin name="GND5" x="25.4" y="-60.96" length="middle" rot="R180"/>
<pin name="GND6" x="81.28" y="0" length="middle"/>
<pin name="GND7" x="111.76" y="0" length="middle" rot="R180"/>
<pin name="5V" x="81.28" y="-2.54" length="middle"/>
<pin name="5V2" x="111.76" y="-2.54" length="middle" rot="R180"/>
<pin name="VDD2" x="81.28" y="-5.08" length="middle"/>
<pin name="VDD3" x="111.76" y="-5.08" length="middle" rot="R180"/>
<pin name="PH0" x="81.28" y="-7.62" length="middle"/>
<pin name="PH1" x="111.76" y="-7.62" length="middle" rot="R180"/>
<pin name="PC14" x="81.28" y="-10.16" length="middle"/>
<pin name="PC15" x="111.76" y="-10.16" length="middle" rot="R180"/>
<pin name="PE6" x="81.28" y="-12.7" length="middle"/>
<pin name="PC13" x="111.76" y="-12.7" length="middle" rot="R180"/>
<pin name="PE4" x="81.28" y="-15.24" length="middle"/>
<pin name="PE5" x="111.76" y="-15.24" length="middle" rot="R180"/>
<pin name="PE2" x="81.28" y="-17.78" length="middle"/>
<pin name="PE3" x="111.76" y="-17.78" length="middle" rot="R180"/>
<pin name="PE0" x="81.28" y="-20.32" length="middle"/>
<pin name="PE1" x="111.76" y="-20.32" length="middle" rot="R180"/>
<pin name="PB8" x="81.28" y="-22.86" length="middle"/>
<pin name="PB9" x="111.76" y="-22.86" length="middle" rot="R180"/>
<pin name="BOOT0" x="81.28" y="-25.4" length="middle"/>
<pin name="VDD4" x="111.76" y="-25.4" length="middle" rot="R180"/>
<pin name="PB6" x="81.28" y="-27.94" length="middle"/>
<pin name="PB7" x="111.76" y="-27.94" length="middle" rot="R180"/>
<pin name="PB4" x="81.28" y="-30.48" length="middle"/>
<pin name="PB5" x="111.76" y="-30.48" length="middle" rot="R180"/>
<pin name="PD7" x="81.28" y="-33.02" length="middle"/>
<pin name="PB3" x="111.76" y="-33.02" length="middle" rot="R180"/>
<pin name="PD5" x="81.28" y="-35.56" length="middle"/>
<pin name="PD6" x="111.76" y="-35.56" length="middle" rot="R180"/>
<pin name="PD3" x="81.28" y="-38.1" length="middle"/>
<pin name="PD4" x="111.76" y="-38.1" length="middle" rot="R180"/>
<pin name="PD1" x="81.28" y="-40.64" length="middle"/>
<pin name="PD2" x="111.76" y="-40.64" length="middle" rot="R180"/>
<pin name="PC12" x="81.28" y="-43.18" length="middle"/>
<pin name="PD0" x="111.76" y="-43.18" length="middle" rot="R180"/>
<pin name="PC10" x="81.28" y="-45.72" length="middle"/>
<pin name="PC11" x="111.76" y="-45.72" length="middle" rot="R180"/>
<pin name="PA14" x="81.28" y="-48.26" length="middle"/>
<pin name="PA15" x="111.76" y="-48.26" length="middle" rot="R180"/>
<pin name="PA10" x="81.28" y="-50.8" length="middle"/>
<pin name="PA13" x="111.76" y="-50.8" length="middle" rot="R180"/>
<pin name="PA8" x="81.28" y="-53.34" length="middle"/>
<pin name="PA9" x="111.76" y="-53.34" length="middle" rot="R180"/>
<pin name="PC8" x="81.28" y="-55.88" length="middle"/>
<pin name="PC9" x="111.76" y="-55.88" length="middle" rot="R180"/>
<pin name="PC6" x="81.28" y="-58.42" length="middle"/>
<pin name="PC7" x="111.76" y="-58.42" length="middle" rot="R180"/>
<pin name="GND8" x="81.28" y="-60.96" length="middle"/>
<pin name="GND9" x="111.76" y="-60.96" length="middle" rot="R180"/>
<pin name="GND1" x="25.4" y="0" length="middle" rot="R180"/>
<pin name="GND2" x="-5.08" y="-5.08" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="STM32F4-DISCOVERY">
<gates>
<gate name="G$1" symbol="STM32F4-DISCOVERY" x="-55.88" y="27.94"/>
</gates>
<devices>
<device name="" package="STM32F4-DISCOVERY">
<connects>
<connect gate="G$1" pin="5V" pad="5V"/>
<connect gate="G$1" pin="5V2" pad="5V2"/>
<connect gate="G$1" pin="BOOT0" pad="BOOT0"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND1" pad="GND1"/>
<connect gate="G$1" pin="GND2" pad="GND2"/>
<connect gate="G$1" pin="GND3" pad="GND3"/>
<connect gate="G$1" pin="GND4" pad="GND4"/>
<connect gate="G$1" pin="GND5" pad="GND5"/>
<connect gate="G$1" pin="GND6" pad="GND6"/>
<connect gate="G$1" pin="GND7" pad="GND7"/>
<connect gate="G$1" pin="GND8" pad="GND8"/>
<connect gate="G$1" pin="GND9" pad="GND9"/>
<connect gate="G$1" pin="NC" pad="NC"/>
<connect gate="G$1" pin="NRST" pad="NRST"/>
<connect gate="G$1" pin="PA0" pad="PA0"/>
<connect gate="G$1" pin="PA1" pad="PA1"/>
<connect gate="G$1" pin="PA10" pad="PA10"/>
<connect gate="G$1" pin="PA13" pad="PA13"/>
<connect gate="G$1" pin="PA14" pad="PA14"/>
<connect gate="G$1" pin="PA15" pad="PA15"/>
<connect gate="G$1" pin="PA2" pad="PA2"/>
<connect gate="G$1" pin="PA3" pad="PA3"/>
<connect gate="G$1" pin="PA4" pad="PA4"/>
<connect gate="G$1" pin="PA5" pad="PA5"/>
<connect gate="G$1" pin="PA6" pad="PA6"/>
<connect gate="G$1" pin="PA7" pad="PA7"/>
<connect gate="G$1" pin="PA8" pad="PA8"/>
<connect gate="G$1" pin="PA9" pad="PA9"/>
<connect gate="G$1" pin="PB0" pad="PB0"/>
<connect gate="G$1" pin="PB1" pad="PB1"/>
<connect gate="G$1" pin="PB10" pad="PB10"/>
<connect gate="G$1" pin="PB11" pad="PB11"/>
<connect gate="G$1" pin="PB12" pad="PB12"/>
<connect gate="G$1" pin="PB13" pad="PB13"/>
<connect gate="G$1" pin="PB14" pad="PB14"/>
<connect gate="G$1" pin="PB15" pad="PB15"/>
<connect gate="G$1" pin="PB2" pad="PB2"/>
<connect gate="G$1" pin="PB3" pad="PB3"/>
<connect gate="G$1" pin="PB4" pad="PB4"/>
<connect gate="G$1" pin="PB5" pad="PB5"/>
<connect gate="G$1" pin="PB6" pad="PB6"/>
<connect gate="G$1" pin="PB7" pad="PB7"/>
<connect gate="G$1" pin="PB8" pad="PB8"/>
<connect gate="G$1" pin="PB9" pad="PB9"/>
<connect gate="G$1" pin="PC0" pad="PC0"/>
<connect gate="G$1" pin="PC1" pad="PC1"/>
<connect gate="G$1" pin="PC10" pad="PC10"/>
<connect gate="G$1" pin="PC11" pad="PC11"/>
<connect gate="G$1" pin="PC12" pad="PC12"/>
<connect gate="G$1" pin="PC13" pad="PC13"/>
<connect gate="G$1" pin="PC14" pad="PC14"/>
<connect gate="G$1" pin="PC15" pad="PC15"/>
<connect gate="G$1" pin="PC2" pad="PC2"/>
<connect gate="G$1" pin="PC3" pad="PC3"/>
<connect gate="G$1" pin="PC4" pad="PC4"/>
<connect gate="G$1" pin="PC5" pad="PC5"/>
<connect gate="G$1" pin="PC6" pad="PC6"/>
<connect gate="G$1" pin="PC7" pad="PC7"/>
<connect gate="G$1" pin="PC8" pad="PC8"/>
<connect gate="G$1" pin="PC9" pad="PC9"/>
<connect gate="G$1" pin="PD0" pad="PD0"/>
<connect gate="G$1" pin="PD1" pad="PD1"/>
<connect gate="G$1" pin="PD10" pad="PD10"/>
<connect gate="G$1" pin="PD11" pad="PD11"/>
<connect gate="G$1" pin="PD12" pad="PD12"/>
<connect gate="G$1" pin="PD13" pad="PD13"/>
<connect gate="G$1" pin="PD14" pad="PD14"/>
<connect gate="G$1" pin="PD15" pad="PD15"/>
<connect gate="G$1" pin="PD2" pad="PD2"/>
<connect gate="G$1" pin="PD3" pad="PD3"/>
<connect gate="G$1" pin="PD4" pad="PD4"/>
<connect gate="G$1" pin="PD5" pad="PD5"/>
<connect gate="G$1" pin="PD6" pad="PD6"/>
<connect gate="G$1" pin="PD7" pad="PD7"/>
<connect gate="G$1" pin="PD8" pad="PD8"/>
<connect gate="G$1" pin="PD9" pad="PD9"/>
<connect gate="G$1" pin="PE0" pad="PE0"/>
<connect gate="G$1" pin="PE1" pad="PE1"/>
<connect gate="G$1" pin="PE10" pad="PE10"/>
<connect gate="G$1" pin="PE11" pad="PE11"/>
<connect gate="G$1" pin="PE12" pad="PE12"/>
<connect gate="G$1" pin="PE13" pad="PE13"/>
<connect gate="G$1" pin="PE14" pad="PE14"/>
<connect gate="G$1" pin="PE15" pad="PE15"/>
<connect gate="G$1" pin="PE2" pad="PE2"/>
<connect gate="G$1" pin="PE3" pad="PE3"/>
<connect gate="G$1" pin="PE4" pad="PE4"/>
<connect gate="G$1" pin="PE5" pad="PE5"/>
<connect gate="G$1" pin="PE6" pad="PE6"/>
<connect gate="G$1" pin="PE7" pad="PE7"/>
<connect gate="G$1" pin="PE8" pad="PE8"/>
<connect gate="G$1" pin="PE9" pad="PE9"/>
<connect gate="G$1" pin="PH0" pad="PH0"/>
<connect gate="G$1" pin="PH1" pad="PH1"/>
<connect gate="G$1" pin="VDD" pad="VDD"/>
<connect gate="G$1" pin="VDD1" pad="VDD1"/>
<connect gate="G$1" pin="VDD2" pad="VDD2"/>
<connect gate="G$1" pin="VDD3" pad="VDD3"/>
<connect gate="G$1" pin="VDD4" pad="VDD4"/>
</connects>
<technologies>
<technology name=""/>
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
<part name="U$1" library="SparkFun-Boards" deviceset="LOGIC_LEVEL_CONVERTER" device=""/>
<part name="U$2" library="STM32F4-DISCOVERY_CF_INTECH" deviceset="STM32F4-DISCOVERY" device=""/>
<part name="J1" library="con-amp" deviceset="MTA03-100" device=""/>
<part name="J2" library="con-amp" deviceset="MTA03-100" device=""/>
<part name="J3" library="con-amp" deviceset="MTA03-100" device=""/>
<part name="J4" library="con-amp" deviceset="MTA03-100" device=""/>
<part name="J5" library="con-amp" deviceset="MTA03-100" device=""/>
<part name="J6" library="con-amp" deviceset="MTA03-100" device=""/>
<part name="J7" library="con-amp" deviceset="MTA03-100" device=""/>
<part name="U$3" library="esp8266modules" deviceset="ESP01" device=""/>
<part name="X1" library="con-ptr500" deviceset="AK300/2" device=""/>
<part name="SUPPLY1" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY2" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY3" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY4" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY5" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY6" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY7" library="supply2" deviceset="GND" device=""/>
<part name="P+1" library="supply1" deviceset="VCC" device=""/>
<part name="P+2" library="supply1" deviceset="VCC" device=""/>
<part name="J8" library="con-amp" deviceset="MTA03-100" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="-27.94" y="-43.18" size="1.778" layer="91">ESP</text>
<text x="60.96" y="-15.24" size="1.778" layer="91">AX12</text>
<text x="-35.56" y="-83.82" size="1.778" layer="91">Converter</text>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="-35.56" y="-127"/>
<instance part="U$2" gate="G$1" x="-63.5" y="58.42"/>
<instance part="J1" gate="G$1" x="35.56" y="-27.94"/>
<instance part="J2" gate="G$1" x="35.56" y="-35.56"/>
<instance part="J3" gate="G$1" x="35.56" y="-43.18"/>
<instance part="J4" gate="G$1" x="35.56" y="-50.8"/>
<instance part="J5" gate="G$1" x="35.56" y="-58.42"/>
<instance part="J6" gate="G$1" x="35.56" y="-66.04"/>
<instance part="J7" gate="G$1" x="35.56" y="-73.66"/>
<instance part="U$3" gate="G$1" x="-45.72" y="-60.96" smashed="yes">
<attribute name="NAME" x="-58.42" y="-50.8" size="1.778" layer="95"/>
<attribute name="VALUE" x="-58.42" y="-66.04" size="1.778" layer="95"/>
</instance>
<instance part="X1" gate="-1" x="22.86" y="-119.38" rot="R180"/>
<instance part="X1" gate="-2" x="22.86" y="-114.3" rot="R180"/>
<instance part="SUPPLY1" gate="GND" x="10.16" y="-121.92"/>
<instance part="SUPPLY2" gate="GND" x="20.32" y="-86.36"/>
<instance part="SUPPLY3" gate="GND" x="0" y="58.42" rot="R270"/>
<instance part="SUPPLY4" gate="GND" x="-86.36" y="58.42" rot="R270"/>
<instance part="SUPPLY5" gate="GND" x="-78.74" y="-53.34" rot="R270"/>
<instance part="SUPPLY6" gate="GND" x="-81.28" y="-104.14" rot="R270"/>
<instance part="SUPPLY7" gate="GND" x="-15.24" y="-104.14" rot="R90"/>
<instance part="P+1" gate="VCC" x="10.16" y="-109.22"/>
<instance part="P+2" gate="VCC" x="30.48" y="-91.44"/>
<instance part="J8" gate="G$1" x="35.56" y="-78.74"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="-66.04" y1="-104.14" x2="-78.74" y2="-104.14" width="0.1524" layer="91"/>
<pinref part="SUPPLY6" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GND@2"/>
<wire x1="-27.94" y1="-104.14" x2="-17.78" y2="-104.14" width="0.1524" layer="91"/>
<pinref part="SUPPLY7" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="GND"/>
<wire x1="-68.58" y1="58.42" x2="-83.82" y2="58.42" width="0.1524" layer="91"/>
<pinref part="SUPPLY4" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="GND6"/>
<wire x1="17.78" y1="58.42" x2="2.54" y2="58.42" width="0.1524" layer="91"/>
<pinref part="SUPPLY3" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="J1" gate="G$1" pin="1"/>
<pinref part="J2" gate="G$1" pin="1"/>
<wire x1="33.02" y1="-30.48" x2="33.02" y2="-38.1" width="0.1524" layer="91"/>
<pinref part="J3" gate="G$1" pin="1"/>
<wire x1="33.02" y1="-45.72" x2="33.02" y2="-38.1" width="0.1524" layer="91"/>
<pinref part="J4" gate="G$1" pin="1"/>
<wire x1="33.02" y1="-53.34" x2="33.02" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="J5" gate="G$1" pin="1"/>
<wire x1="33.02" y1="-60.96" x2="33.02" y2="-53.34" width="0.1524" layer="91"/>
<pinref part="J6" gate="G$1" pin="1"/>
<wire x1="33.02" y1="-68.58" x2="33.02" y2="-60.96" width="0.1524" layer="91"/>
<pinref part="J7" gate="G$1" pin="1"/>
<wire x1="33.02" y1="-76.2" x2="33.02" y2="-68.58" width="0.1524" layer="91"/>
<wire x1="33.02" y1="-83.82" x2="33.02" y2="-81.28" width="0.1524" layer="91"/>
<wire x1="33.02" y1="-81.28" x2="33.02" y2="-76.2" width="0.1524" layer="91"/>
<wire x1="33.02" y1="-83.82" x2="20.32" y2="-83.82" width="0.1524" layer="91"/>
<pinref part="SUPPLY2" gate="GND" pin="GND"/>
<pinref part="J8" gate="G$1" pin="1"/>
<junction x="33.02" y="-81.28"/>
</segment>
<segment>
<pinref part="U$3" gate="G$1" pin="GND"/>
<wire x1="-63.5" y1="-53.34" x2="-76.2" y2="-53.34" width="0.1524" layer="91"/>
<pinref part="SUPPLY5" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="X1" gate="-1" pin="KL"/>
<wire x1="17.78" y1="-119.38" x2="10.16" y2="-119.38" width="0.1524" layer="91"/>
<pinref part="SUPPLY1" gate="GND" pin="GND"/>
</segment>
</net>
<net name="3.3V" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="LV"/>
<wire x1="-66.04" y1="-101.6" x2="-78.74" y2="-101.6" width="0.1524" layer="91"/>
<label x="-78.74" y="-101.6" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="VDD"/>
<wire x1="-68.58" y1="55.88" x2="-83.82" y2="55.88" width="0.1524" layer="91"/>
<label x="-83.82" y="55.88" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$3" gate="G$1" pin="VCC"/>
<wire x1="-30.48" y1="-60.96" x2="-17.78" y2="-60.96" width="0.1524" layer="91"/>
<label x="-17.78" y="-60.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="5V" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="HV"/>
<wire x1="-27.94" y1="-101.6" x2="-17.78" y2="-101.6" width="0.1524" layer="91"/>
<label x="-17.78" y="-101.6" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="5V"/>
<wire x1="17.78" y1="55.88" x2="2.54" y2="55.88" width="0.1524" layer="91"/>
<label x="2.54" y="55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="STM_RX_TX" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="PA3"/>
<wire x1="-68.58" y1="43.18" x2="-83.82" y2="43.18" width="0.1524" layer="91"/>
<label x="-83.82" y="43.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PA2"/>
<wire x1="-38.1" y1="43.18" x2="-33.02" y2="43.18" width="0.1524" layer="91"/>
<label x="-33.02" y="43.18" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="LV_TXI_1"/>
<wire x1="-66.04" y1="-96.52" x2="-78.74" y2="-96.52" width="0.1524" layer="91"/>
<label x="-78.74" y="-96.52" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="LV_RXO_1"/>
<wire x1="-66.04" y1="-99.06" x2="-78.74" y2="-99.06" width="0.1524" layer="91"/>
<label x="-78.74" y="-99.06" size="1.778" layer="95"/>
</segment>
</net>
<net name="AX12_RX_TX" class="0">
<segment>
<pinref part="J7" gate="G$1" pin="3"/>
<wire x1="38.1" y1="-83.82" x2="38.1" y2="-81.28" width="0.1524" layer="91"/>
<pinref part="J6" gate="G$1" pin="3"/>
<wire x1="38.1" y1="-81.28" x2="38.1" y2="-76.2" width="0.1524" layer="91"/>
<wire x1="38.1" y1="-76.2" x2="38.1" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="J5" gate="G$1" pin="3"/>
<wire x1="38.1" y1="-68.58" x2="38.1" y2="-60.96" width="0.1524" layer="91"/>
<pinref part="J4" gate="G$1" pin="3"/>
<wire x1="38.1" y1="-60.96" x2="38.1" y2="-53.34" width="0.1524" layer="91"/>
<pinref part="J3" gate="G$1" pin="3"/>
<wire x1="38.1" y1="-53.34" x2="38.1" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="J2" gate="G$1" pin="3"/>
<wire x1="38.1" y1="-45.72" x2="38.1" y2="-38.1" width="0.1524" layer="91"/>
<pinref part="J1" gate="G$1" pin="3"/>
<wire x1="38.1" y1="-38.1" x2="38.1" y2="-30.48" width="0.1524" layer="91"/>
<wire x1="38.1" y1="-83.82" x2="50.8" y2="-83.82" width="0.1524" layer="91"/>
<label x="50.8" y="-83.82" size="1.778" layer="95"/>
<pinref part="J8" gate="G$1" pin="3"/>
<junction x="38.1" y="-81.28"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="HV_TXO_1"/>
<wire x1="-27.94" y1="-96.52" x2="-17.78" y2="-96.52" width="0.1524" layer="91"/>
<label x="-17.78" y="-96.52" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="HV_RXI_1"/>
<wire x1="-27.94" y1="-99.06" x2="-17.78" y2="-99.06" width="0.1524" layer="91"/>
<label x="-17.78" y="-99.06" size="1.778" layer="95"/>
</segment>
</net>
<net name="ESP_RX" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="RXD"/>
<wire x1="-63.5" y1="-60.96" x2="-76.2" y2="-60.96" width="0.1524" layer="91"/>
<label x="-76.2" y="-60.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PC6"/>
<wire x1="17.78" y1="0" x2="10.16" y2="0" width="0.1524" layer="91"/>
<label x="10.16" y="0" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="GPIO2"/>
<wire x1="-63.5" y1="-55.88" x2="-76.2" y2="-55.88" width="0.1524" layer="91"/>
<label x="-76.2" y="-55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="GPIO0"/>
<wire x1="-63.5" y1="-58.42" x2="-76.2" y2="-58.42" width="0.1524" layer="91"/>
<label x="-76.2" y="-58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="ESP_TX" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="TXD"/>
<wire x1="-30.48" y1="-53.34" x2="-17.78" y2="-53.34" width="0.1524" layer="91"/>
<label x="-17.78" y="-53.34" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="PC7"/>
<wire x1="48.26" y1="0" x2="55.88" y2="0" width="0.1524" layer="91"/>
<label x="55.88" y="0" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="CH_PD"/>
<wire x1="-30.48" y1="-55.88" x2="-17.78" y2="-55.88" width="0.1524" layer="91"/>
<label x="-17.78" y="-55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="RST"/>
<wire x1="-30.48" y1="-58.42" x2="-17.78" y2="-58.42" width="0.1524" layer="91"/>
<label x="-17.78" y="-58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="VCC" class="0">
<segment>
<pinref part="X1" gate="-2" pin="KL"/>
<wire x1="17.78" y1="-114.3" x2="10.16" y2="-114.3" width="0.1524" layer="91"/>
<pinref part="P+1" gate="VCC" pin="VCC"/>
<wire x1="10.16" y1="-114.3" x2="10.16" y2="-111.76" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="30.48" y1="-93.98" x2="30.48" y2="-96.52" width="0.1524" layer="91"/>
<pinref part="J7" gate="G$1" pin="2"/>
<wire x1="35.56" y1="-96.52" x2="35.56" y2="-81.28" width="0.1524" layer="91"/>
<pinref part="J6" gate="G$1" pin="2"/>
<wire x1="35.56" y1="-81.28" x2="35.56" y2="-76.2" width="0.1524" layer="91"/>
<wire x1="35.56" y1="-76.2" x2="35.56" y2="-68.58" width="0.1524" layer="91"/>
<pinref part="J5" gate="G$1" pin="2"/>
<wire x1="35.56" y1="-68.58" x2="35.56" y2="-60.96" width="0.1524" layer="91"/>
<pinref part="J4" gate="G$1" pin="2"/>
<wire x1="35.56" y1="-60.96" x2="35.56" y2="-53.34" width="0.1524" layer="91"/>
<pinref part="J3" gate="G$1" pin="2"/>
<wire x1="35.56" y1="-53.34" x2="35.56" y2="-45.72" width="0.1524" layer="91"/>
<pinref part="J2" gate="G$1" pin="2"/>
<wire x1="35.56" y1="-45.72" x2="35.56" y2="-38.1" width="0.1524" layer="91"/>
<pinref part="J1" gate="G$1" pin="2"/>
<wire x1="35.56" y1="-38.1" x2="35.56" y2="-30.48" width="0.1524" layer="91"/>
<wire x1="30.48" y1="-96.52" x2="35.56" y2="-96.52" width="0.1524" layer="91"/>
<pinref part="P+2" gate="VCC" pin="VCC"/>
<pinref part="J8" gate="G$1" pin="2"/>
<junction x="35.56" y="-81.28"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
