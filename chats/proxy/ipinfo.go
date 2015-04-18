package proxy

type IpInfo struct {
	Ip       string `json:"ip"`
	HostName string `json:"hostname"`
	City     string `json:"city"`
	Region   string `json:"region"`
	Country  string `json:"country"`
	Loc      string `json:"loc"`
	Org      string `json:"org"`
}

/*
{
  "ip": "124.205.66.66",
  "hostname": "No Hostname",
  "city": "Beijing",
  "region": "Beijing",
  "country": "CN",
  "loc": "39.9289,116.3883",
  "org": "AS4847 China Networks Inter-Exchange"
}
*/
