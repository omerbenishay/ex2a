#include <iostream>
#include <string>
#include "examDetails.h"
#include <cmath>

using namespace mtm;

const int mtmExam_course_number = 234124;
const int mtmExam_month = 7;
const int mtmExam_day = 28;
const double mtmExam_time = 13;
const int mtmExam_duration = 3;
const std::string mtmExam_link = "https://tinyurl.com/59hzps6m";
const int days_in_month = 30;

ExamDetails::ExamDetails(int course_number, int month, int day, double time, int duration, std::string link)
{
    checkArgs(course_number, month, day, time, duration);
    this->course_number = course_number;
    this->month = month;
    this->day = day;
    this->time = time;
    this->duration = duration;
    this->link = link;
}

void checkArgs(int course_number, int month, int day, double time, int duration)
{
    if(course_number <= 0) { //check!!
        throw ExamDetails::InvalidArgsException();
    }
    if(month <= 0 || month > 13) {
        throw ExamDetails::InvalidDateException();
    }
    if(day < 1 || day > 30){
        throw ExamDetails::InvalidDateException();
    }
    if(time < 0 || time >= 24) {
        throw ExamDetails::InvalidTimeException();
    }
    double intpart;
    double fract_part = std::modf(time, &intpart);
    if(fract_part != 0.5 || fract_part != 0) {
        throw ExamDetails::InvalidTimeException();
    }
    if(duration <= 0) { //check!!
        throw ExamDetails::InvalidArgsException();
    }
}

ExamDetails::ExamDetails(const ExamDetails& exam) : 
    course_number(exam.course_number) ,
    month(exam.month) , 
    day(exam.day) ,
    time(exam.time) ,
    duration(exam.duration) ,
    link(exam.link){}

ExamDetails ExamDetails::makeMatamExam()
{
    return ExamDetails(mtmExam_course_number,
                    mtmExam_month,
                    mtmExam_day,
                    mtmExam_time,
                    mtmExam_duration,
                    mtmExam_link);
}
ExamDetails& ExamDetails::operator=(const ExamDetails& exam)
{
    course_number = exam.course_number;
    month = exam.month;
    day = exam.day;
    time = exam.time;
    duration = exam.duration;
    link = exam.link;
    return *this;
}
std::string ExamDetails::getLink() const
{
    return link;
}
void ExamDetails::setLink(const std::string new_link)
{
    link = new_link;
}
int ExamDetails::operator-(const ExamDetails& exam) const
{
    return (month - exam.month)*days_in_month + (day - exam.day);
}
bool ExamDetails::operator<(const ExamDetails& exam) const
{
    int delta = *this - exam;
    if(delta > 0){
        return false;
    }
    if(delta < 0){
        return true;
    }
    if(time + duration < exam.time){
        return true;
    }
    return false;
}


std::ostream& mtm::operator<<(std::ostream& os, const ExamDetails& exam)
{
    double intpart;
    double fract_part = std::modf(exam.time, &intpart);
    os << "Course Number:" << exam.course_number << std::endl;
    os << "Time:" << exam.day << '.' << exam.month << "at";
    if(fract_part == 0.5)
    {
        os << intpart << ":30" << std::endl;
    }
    else{
        os << intpart << ":00" << std::endl;
    }
    os << "Duration:" << exam.duration << ":00" << std::endl;
    os << "Zoom link:" << exam.link << std::endl;
    return os;
}

