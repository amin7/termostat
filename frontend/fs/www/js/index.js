var termInfo = {
    date_time: ko.observable("date"),
    temperature_flour_cur: ko.observable(),
    temperature_flour_set: ko.observable(),
    heaterIcon:ko.observable(),
    temperature_air: ko.observable(),
    temperature_humidity: ko.observable(),
    mode: ko.observable(),
    temperature_valDay: ko.observable(),
    temperature_valNight: ko.observable(),
    temperature_valVacation: ko.observable(),
    isConfigChanged: ko.observable(false)
};

function index_on_load(){
    ko.applyBindings(termInfo);
    SendGetHttp("/about", index_answer_about,on_ResponceErrorLog);
    SendGetHttp("/status", index_answer_state,on_ResponceErrorLog);
    termInfo.temperature_flour_cur(25.4);
    termInfo.temperature_flour_set(25);
    termInfo.heaterIcon(get_icon_svg("arrow-up", "1.3em", "1.2em"))
    termInfo.temperature_valDay(25);
}

function index_answer_about(response_text) {
    try { 
        var response = JSON.parse(response_text);
        console.log(response);
        document.title = response.deviceName +" ui"
    } catch (e) {
        console.error("Parsing error:", e);
    }
}

function index_answer_state(response_text) {
    try { 
        var response = JSON.parse(response_text);
        console.log(response);
    } catch (e) {
        console.error("Parsing error:", e);
    }
}
