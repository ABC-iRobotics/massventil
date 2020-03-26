# MultiVent

Open Source multi-patient medical ventilator for massive emergency situations - ABC-iRobotics/multivent

## Comparison of open-hardware ventilator projects

### Parameters

| Parameter | Type | Description |
|---|---|---|
|**Project**|string|Name of the project|
|**Institute**|string|Name of the organization|
|**Links**|string|Online materials|
|**Air supply**|enum{ambu-bag, wall outlet, built-in}|Type of air supply: [Ambu-bag](https://www.ambu.com/clinical-studies/ambu-resuscitator), hospital wall outlet or built-in solution|
|**Long-term**|bool|Intended for continuous use for many hours|
|**Nr outputs**|int|Number of patients the device can serve parallel|
|**Actuator**|string| Mechanism|
|**Adjustable volume**|enum{none, discrate, continuous}||
|**Adjustable speed**|enum{none, discrate, continuous}|Breaths per minute adjustable|
|**UI**|string|Type of user interface|
|**Pressure ctrl**|bool|Controlled pressure|
|**Safety**|string|Safety features|
|**Price**|int|Estimated bulk-manufacturing price in $|


### Comparison table

| Project | Institute | Links | Air supply | Long-term | Nr outputs | Actuator | Adjustable volume | Adjustable speed | UI | Pressure ctrl | Safety | Price |
| --- | --- | --- | :---: | :---: | --- | --- | --- | --- | --- | :---: | --- | --- |
| MultiVent | [IROB - OE](http://irob.uni-obuda.hu/?q=en) | [GitHub](https://github.com/ABC-iRobotics/multivent) | built-in | ✓ | 5 | Industrial vacuum cleaner motor | ? | ? | ? | ✓ | ? | ? |
| Take a Breather | [OEDK - RICE](http://oedk.rice.edu/)| [article](https://news.rice.edu/2019/05/01/student-invention-gives-patients-the-breath-of-life-2/), [public profile](http://oedk.rice.edu/Sys/PublicProfile/47585242/1063096)  | Ambu-bag | ✓ | 1 | Rack & pinion | discrete | discrete | LCD and buttons | X | none | ? |
| Low-cost Portable Mechanical Ventilator | Institute | [paper](https://e-vent.mit.edu/wp-content/uploads/2020/03/DMD-2010-MIT-E-Vent.pdf) | Ambu-bag | X | 1 | Pivoting cam arm | Continuous | Continuous | Knobs | ✓ | Over-pressure alarm | 200 |

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
- https://e-vent.mit.edu/?fbclid=IwAR1Wt48dTyqpNfGEb84gJkT1yPgEH7q8lvXa1uf27n4UiYYlMUPQMVIO6hE
- https://24.hu/belfold/2020/03/26/koronavirus-lelegeztetogep-egeszsegugy/
- https://www.europeanscientist.com/en/public-health/an-open-source-respirator-for-40-euros-from-a-3d-printer/
- https://www.bbc.com/news/technology-52021757
- https://hackaday.com/2020/03/25/ventilators-101-what-they-do-and-how-they-work/?fbclid=IwAR0Zt14DeGQpgK3idkqEPmunTQudY1Sa7-hktxozl5Tdq36QGEqKXfKEjz4

