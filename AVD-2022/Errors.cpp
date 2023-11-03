#include "Error.h"
namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Íåäîïóñòèìûé êîä îøèáêè"),
		ERROR_ENTRY(1, "Ñèñòåìíûé ñáîé"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50, "Íåòó ïàğàìåòğîâ"),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Ïàğàìåòğ -in äîëæåí áûòü çàäàí"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Ïğåâûøåíà äëèíà âõîäíîãî ïàğàìåòğà"),
		ERROR_ENTRY(105, "Ïğåâûøåíà äëèíà òàáëèöû èäåíòèôèêàòîğîâ"),
		ERROR_ENTRY(106, "Ïğåâûøåíà äëèíà òàáëèöû ëåêñåì"),
		ERROR_ENTRY(107, "Ïğåâûøåíà äëèíà èäåíòèôèêàòîğà"),
		ERROR_ENTRY(108, "Ëåêñåìà íå ğàñïîçíàíà"),
		ERROR_ENTRY(109, "Ïğåâûøåí ğàçìåğ ëèòåğàëà"),
		ERROR_ENTRY(110, "Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)"),
		ERROR_ENTRY(111, "Íåäîïóñòèìûé ñèìâîë â èñõîäíîì êîäå (-in)"),
		ERROR_ENTRY(112, "Îøèáêà ïğè ñîçäàíèè ôàéëà ïğîòîêîëà (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY(300, "Íåîáúÿâëåííûé èäåíòèôèêàòîğ"),
		ERROR_ENTRY(301, "Îòñóòñòâóåò òî÷êà âõîäà main"),
		ERROR_ENTRY(302, "Îáíàğóæåíî íåñêîëüêî òî÷åê âõîäà main"),
		ERROR_ENTRY(303, "Ïîïûòêà ïåğåîïğåäåëåíèÿ èäåíòèôèêàòîğà"),
		ERROR_ENTRY(304, "Ïğåâûøåíî ìàêñèìàëüíîå êîëè÷åñòâî ïàğàìåòğîâ ôóíêöèè"),
		ERROR_ENTRY(305, "Ñëèøêîì ìíîãî ïàğàìåòğîâ â âûçîâå"),
		ERROR_ENTRY(306, "Êîë-âî îæèäàåìûåõ ôóíêöèåé è ïåğåäàâàåìûõ ïàğàìåòğîâ íå ñîâïàäàşò"),
		ERROR_ENTRY(307, "Íåñîâïàäåíèå òèïîâ ïåğåäàâàåìûõ ïàğàìåòğîâ"),
		ERROR_ENTRY(308, "Ïğåâûøåí ğàçìåğ ñòğîêîâîãî ëèòåğàëà"),
		ERROR_ENTRY(309, "Òèïû äàííûõ â âûğàæåíèè íå ñîâïàäàşò"),
		ERROR_ENTRY(310, "Òèï ôóíêöèè è âîçâğàùàåìîãî çíà÷åíèÿ íå ñîâïàäàşò"),
		ERROR_ENTRY(311, "Íåäîïóñòèìîå ñòğîêîâîå âûğàæåíèå ñïğàâà îò çíàêà ="),
		ERROR_ENTRY(312, "Íåâåğíîå óñëîâíîå âûğàæåíèå"),
		ERROR_ENTRY(313, "Äåëåíèå íà íîëü"),
		ERROR_ENTRY(314, "Âûğàæåíèå äîëæíî áûòü óñëîâíûì"),
		ERROR_ENTRY(315, "Ïğåâûøåí ğàçìåğ öåëî÷èñëåííîãî ëèòåğàëà"),
		ERROR_ENTRY(316, "Ïîïûòêà ïğèñâîèòü îòğèöàòåëüíîå çíà÷åíèå"),
		ERROR_ENTRY_NODEF(317),ERROR_ENTRY_NODEF(318),ERROR_ENTRY_NODEF(319),
		ERROR_ENTRY_NODEF10(320),ERROR_ENTRY_NODEF10(330),ERROR_ENTRY_NODEF10(340),ERROR_ENTRY_NODEF10(350),
		ERROR_ENTRY_NODEF10(360),ERROR_ENTRY_NODEF10(370),ERROR_ENTRY_NODEF10(380),ERROR_ENTRY_NODEF10(390),
		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600,"Íåâåğíàÿ ñòğóêòóğà ïğîãğàììû"),
		ERROR_ENTRY(601,"Îøèáî÷íûé îïåğàòîğ"),
		ERROR_ENTRY(602,"Îøèáêà â âûğàæåíèè"),
		ERROR_ENTRY(603,"Îøèáêà â ïàğàìåòğàõ ôóíêöèè"),
		ERROR_ENTRY(604,"Îøèáêà â ïàğàìåòğàõ âûçûâàåìîé ôóíêöèè"),
		ERROR_ENTRY(605,"Îøèáêà â ïîäâûğàæåíèè"),
		ERROR_ENTRY(606, "Íåâåğíûé ñèíòàêñèñ ôóíêöèè"),
		ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF10(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror(int id)
	{
		if (id >= 0 && id < ERROR_MAX_ENTRY)
			return errors[id];
		return errors[0];
	}
	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if (0 < id < ERROR_MAX_ENTRY)
		{
			errors[id].inext.col = col;
			errors[id].inext.line = line;
			return errors[id];
		}
		else errors[0];
	}
}