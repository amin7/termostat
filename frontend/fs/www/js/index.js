var termInfo = {
    info:{
        date_time: ko.observable("date"),
        temperature:{
            heaterIcon:ko.observable(),
            flour_cur: ko.observable(),
            flour_set: ko.observable(),
            air: ko.observable(),
        },
        humidity: ko.observable(),
        mode: ko.observable(),
    },
    config:{
        isChanged: ko.observable(false),
        temperature:{
            Day: ko.observable(),
            Night: ko.observable(),
            Vacation: ko.observable(),
        },
    },
    vacation:{
        isChanged: ko.observable(false),
        isActive: ko.observable(false),
        from: ko.observable(new Date().toISOString().slice(0,10)),
        to: ko.observable(new Date().toISOString().slice(0,10)),
        temperature: ko.observable(12),
    }
};

function configChanged(){
    termInfo.config.isChanged(true);
}

function index_on_load(){
    ko.applyBindings(termInfo);
    termInfo.info.temperature.flour_cur(25.4);
    termInfo.info.temperature.flour_set(25);
    termInfo.info.temperature.heaterIcon(get_icon_svg("arrow-up", "1.3em", "1.2em"))
    termInfo.info.date_time(new Date())


    termInfo.config.temperature.Day.subscribe(function(newValue) {
        configChanged();
    });
    termInfo.config.temperature.Night.subscribe(function(newValue) {
        configChanged();
    });

    SendGetHttp("/about", index_answer_about,on_ResponceErrorLog);
    SendGetHttp("/status", index_answer_state,on_ResponceErrorLog);
    config_load();
}

function config_save(){
    termInfo.config.isChanged(false);
}

function config_load(){
    termInfo.config.temperature.Day(25);
    termInfo.config.temperature.Night(18);
    termInfo.vacation.temperature(12);
    termInfo.config.isChanged(false);
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

function vacation_set(){
    console.log(termInfo.vacation.isActive(),termInfo.vacation.from(),termInfo.vacation.to(),termInfo.vacation.temperature());

}
