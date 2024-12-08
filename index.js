const fs = require("fs");

const dates = [
    {
        "ts": 1667091600,
        "time": "2022-10-30T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1679792400,
        "time": "2023-03-26T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1698541200,
        "time": "2023-10-29T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1711846800,
        "time": "2024-03-31T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1729990800,
        "time": "2024-10-27T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1743296400,
        "time": "2025-03-30T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1761440400,
        "time": "2025-10-26T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1774746000,
        "time": "2026-03-29T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1792890000,
        "time": "2026-10-25T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1806195600,
        "time": "2027-03-28T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1824944400,
        "time": "2027-10-31T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1837645200,
        "time": "2028-03-26T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1856394000,
        "time": "2028-10-29T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1869094800,
        "time": "2029-03-25T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1887843600,
        "time": "2029-10-28T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1901149200,
        "time": "2030-03-31T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1919293200,
        "time": "2030-10-27T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1932598800,
        "time": "2031-03-30T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1950742800,
        "time": "2031-10-26T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1964048400,
        "time": "2032-03-28T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 1982797200,
        "time": "2032-10-31T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 1995498000,
        "time": "2033-03-27T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 2014246800,
        "time": "2033-10-30T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 2026947600,
        "time": "2034-03-26T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 2045696400,
        "time": "2034-10-29T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 2058397200,
        "time": "2035-03-25T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 2077146000,
        "time": "2035-10-28T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 2090451600,
        "time": "2036-03-30T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 2108595600,
        "time": "2036-10-26T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    },
    {
        "ts": 2121901200,
        "time": "2037-03-29T01:00:00+0000",
        "offset": 10800,
        "isdst": true,
        "abbr": "EEST"
    },
    {
        "ts": 2140045200,
        "time": "2037-10-25T01:00:00+0000",
        "offset": 7200,
        "isdst": false,
        "abbr": "EET"
    }
];

const short = {};
for(let i=0; i<dates.length-1; i+=2){
    let date1 = new Date(dates[i]["time"]);
    let date2 = new Date(dates[i+1]["time"]);
    short[date1.getFullYear()] = {
        first: {
            day: date1.getDate(),
            month: date1.getMonth()+1,
            offset: dates[i].offset
        },
        second: {
            day: date2.getDate(),
            month: date2.getMonth()+1,
            offset: dates[i+1].offset
        }
    };
}

fs.writeFileSync("dates.txt", JSON.stringify(short));