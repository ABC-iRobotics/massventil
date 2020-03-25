# MultiVent

Open Source multi-patient medical ventilator for massive emergency situations - ABC-iRobotics/multivent

## Comparison of open-hardware ventilator projects

### Parameters

| Parameter | Type | Description |
|---|---|---|
|**Ambu-bag**|bool|Incorporates an [Ambu-bag](https://www.ambu.com/clinical-studies/ambu-resuscitator)|
|**Long-term**|bool|Intended for continuous use for many hours|
|**Nr outputs**|int|Number of patients the device can serve parallel|
|**Actuator**|string| Mechanism|
|**Adjustable volume**|enum{none, discrate, continuous}||
|**Adjustable speed**|enum{none, discrate, continuous}|Breaths per minute adjustable|
|**UI**|string|Type of user interface|
|**Pressure ctrl**|bool|Controlled pressure|
|**Safety**|string|Safety features|


### Comparison table

| Project | Links | Ambu-bag | Long-term | Nr outputs | Actuator | Adjustable volume | Adjustable speed | UI | Pressure ctrl | Safety |
| --- | --- | :---: | :---: | --- | --- | --- | --- | --- | :---: | --- |
| [Take a Breather](http://oedk.rice.edu/Sys/PublicProfile/47585242/1063096) | [Article](https://news.rice.edu/2019/05/01/student-invention-gives-patients-the-breath-of-life-2/), | ✓ | ✓ | 1 | Rack & pinion | discrete | discrete | UI | X | none |

### Arbitrary links

#### Found by @haidegger

- https://www.statnews.com/2020/03/21/coronavirus-plea-from-italy-treat-patients-at-home/
- https://blog.arduino.cc/2020/03/17/designing-a-low-cost-open-source-ventilator-with-arduino/
- https://www.techradar.com/news/an-open-source-respirator-could-help-fight-coronavirus
- https://opensource.com/article/20/3/open-hardware-covid19
- https://www.vice.com/en_us/article/5dm4mb/people-are-trying-to-make-diy-ventilators-to-meet-coronavirus-demand
- https://www.nbcnews.com/tech/innovation/worldwide-hackathon-hospitals-turn-crowdsourcing-3d-printing-amid-equipment-shortages-n1165026
- https://www.3dprintingmedia.network/covid-19-3d-printed-valve-for-reanimation-device/
- https://www.forbes.com/sites/amyfeldman/2020/03/19/talking-with-the-italian-engineers-who-3d-printed-respirator-parts-for-hospitals-with-coronavirus-patients-for-free/#2c4bafd978f1

- https://e-vent.mit.edu/?fbclid=IwAR1Wt48dTyqpNfGEb84gJkT1yPgEH7q8lvXa1uf27n4UiYYlMUPQMVIO6hE

#### Found by @wlfdm

- https://e-vent.mit.edu/wp-content/uploads/2020/03/DMD-2010-MIT-E-Vent.pdf
- http://www.onebreathventilators.com/	
- http://oedk.rice.edu/Sys/PublicProfile/47585242/1063096


