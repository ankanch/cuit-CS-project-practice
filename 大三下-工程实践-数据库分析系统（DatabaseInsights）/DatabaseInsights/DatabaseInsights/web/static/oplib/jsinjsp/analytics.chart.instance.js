/* 
 * The MIT License
 *
 * *** Copyright © Long Zhang(kanch)
 * *** Email: kanchisme@gmail.com
 * *** Code created on Jun 07 2018
 *
 * 该类提供了对Echarts选项实例化的功能函数
 */

function initChartWithOption(id, option) {
    var myChart = echarts.init(document.getElementById(id));
    myChart.setOption(option);
}

function initChartWithOptionBySelector(selector, option) {
    var myChart = echarts.init($(selector));
    myChart.setOption(option);
}