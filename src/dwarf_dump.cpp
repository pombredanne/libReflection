#include <fcntl.h>
#include <elfutils/libdw.h>
#include <dwarf.h>
#include <iostream>
#include <iomanip>
std::string getTypename(Dwarf_Attribute *typeAttr){
    if(!typeAttr) return "void";
    Dwarf_Attribute *attr, attrMem;
    Dwarf_Die *res, resMem;
    res=dwarf_formref_die(typeAttr, &resMem);
    if(!res) return "(WTF)";
    switch(dwarf_tag(res)){
        case DW_TAG_class_type:
        case DW_TAG_structure_type:
        case DW_TAG_union_type:
        case DW_TAG_enumeration_type:
        case DW_TAG_base_type:
        case DW_TAG_typedef:
            attr=dwarf_attr_integrate(res, DW_AT_name, &attrMem);
            if(attr) return dwarf_formstring(attr);
            else return "(anonymous)";
        case DW_TAG_pointer_type:
            return getTypename(dwarf_attr_integrate(res, DW_AT_type, &attrMem))+"*";
        case DW_TAG_reference_type:
            return getTypename(dwarf_attr_integrate(res, DW_AT_type, &attrMem))+"&";
        case DW_TAG_rvalue_reference_type:
            return getTypename(dwarf_attr_integrate(res, DW_AT_type, &attrMem))+"&&";
        case DW_TAG_const_type:
            return getTypename(dwarf_attr_integrate(res, DW_AT_type, &attrMem))+" const";
        case DW_TAG_volatile_type:
            return getTypename(dwarf_attr_integrate(res, DW_AT_type, &attrMem))+" volatile";
        case DW_TAG_restrict_type:
            return getTypename(dwarf_attr_integrate(res, DW_AT_type, &attrMem))+" __restrict__";
        case DW_TAG_array_type:
            return "(array)";
        default:
            return "(unknown)";
    }
}
size_t indent;
void handleFunction(Dwarf_Die *funct){
    bool b;
    Dwarf_Die result;
    Dwarf_Attribute *attr, attrMem;
    std::cout<<std::setw(indent)<<""<<"function"<<std::endl;
    indent+=2;
    attr=dwarf_attr_integrate(funct, DW_AT_artificial, &attrMem);
    b=0;
    if(attr){
        dwarf_formflag(attr, &b);
        if(b) std::cout<<std::setw(indent)<<""<<"artificial"<<std::endl;
    }
    if(!b){
        attr=dwarf_attr_integrate(funct, DW_AT_name, &attrMem);
        if(attr) std::cout<<std::setw(indent)<<""<<"name: "<<dwarf_formstring(attr)<<std::endl;
    }
    attr=dwarf_attr_integrate(funct, DW_AT_type, &attrMem);
    std::cout<<std::setw(indent)<<""<<"return type: "<<getTypename(attr)<<std::endl;
    if(!dwarf_child(funct, &result)){
        do{
            switch(dwarf_tag(&result)){
                case DW_TAG_formal_parameter:
                    if(!attr) break;
                    std::cout<<std::setw(indent)<<""<<"parameter"<<std::endl;
                    indent+=2;
                    attr=dwarf_attr_integrate(&result, DW_AT_artificial, &attrMem);
                    b=0;
                    if(attr){
                        dwarf_formflag(attr, &b);
                        if(b) std::cout<<std::setw(indent)<<""<<"artificial"<<std::endl;
                    }
                    if(!b){
                        attr=dwarf_attr_integrate(&result, DW_AT_name, &attrMem);
                        if(attr) std::cout<<std::setw(indent)<<""<<"name: "<<dwarf_formstring(attr)<<std::endl;
                    }
                    attr=dwarf_attr_integrate(&result, DW_AT_type, &attrMem);
                    std::cout<<std::setw(indent)<<""<<"type: "<<getTypename(attr)<<std::endl;
                    indent-=2;
                    break;
                default:
                    break;
            }
        }while(!dwarf_siblingof(&result, &result));
    }
    indent-=2;
    return;
}

void handleVariable(Dwarf_Die *var){
    Dwarf_Attribute *attr, attrMem;
    std::cout<<std::setw(indent)<<""<<"variable"<<std::endl;
    indent+=2;
    attr=dwarf_attr_integrate(var, DW_AT_name, &attrMem);
    if(attr) std::cout<<std::setw(indent)<<""<<"name: "<<dwarf_formstring(attr)<<std::endl;
    attr=dwarf_attr_integrate(var, DW_AT_type, &attrMem);
    std::cout<<std::setw(indent)<<""<<"type: "<<getTypename(attr)<<std::endl;
    indent-=2;
    return;
}
void handleStruct(Dwarf_Die *cl){
    Dwarf_Attribute *attr, attrMem;
    std::cout<<std::setw(indent)<<"";
    switch(dwarf_tag(cl)){
        case DW_TAG_class_type:
            std::cout<<"class";
            break;
        case DW_TAG_structure_type:
            std::cout<<"struct";
            break;
        case DW_TAG_union_type:
            std::cout<<"union";
            break;
    };
    std::cout<<std::endl;
    indent+=2;
    attr=dwarf_attr_integrate(cl, DW_AT_name, &attrMem);
    if(attr) std::cout<<std::setw(indent)<<""<<"name: "<<dwarf_formstring(attr)<<std::endl;
    Dwarf_Die result;
    if(!dwarf_child(cl, &result)){
        do{
            switch(dwarf_tag(&result)){
                case DW_TAG_member:
                    std::cout<<std::setw(indent)<<""<<"member"<<std::endl;
                    indent+=2;
                    attr=dwarf_attr_integrate(&result, DW_AT_name, &attrMem);
                    if(attr) std::cout<<std::setw(indent)<<""<<"name: "<<dwarf_formstring(attr)<<std::endl;
                    attr=dwarf_attr_integrate(&result, DW_AT_type, &attrMem);
                    std::cout<<std::setw(indent)<<""<<"type: "<<getTypename(attr)<<std::endl;
                    indent-=2;
                    break;
                case DW_TAG_subprogram:
                    handleFunction(&result);
                    break;
                default:
                    break;
            }
        }while(!dwarf_siblingof(&result, &result));
    }
    indent-=2;
    return;
}
void handleEnum(Dwarf_Die *en){
    Dwarf_Attribute *attr, attrMem;
    std::cout<<std::setw(indent)<<""<<"variable"<<std::endl;
    indent+=2;
    attr=dwarf_attr_integrate(en, DW_AT_name, &attrMem);
    if(attr) std::cout<<std::setw(indent)<<""<<"name: "<<dwarf_formstring(attr)<<std::endl;
    attr=dwarf_attr_integrate(en, DW_AT_type, &attrMem);
    if(attr) std::cout<<std::setw(indent)<<""<<"underlying type: "<<getTypename(attr)<<std::endl;
    Dwarf_Die result;
    if(!dwarf_child(en, &result)){
        do{
            switch(dwarf_tag(&result)){
                case DW_TAG_enumerator:
                    if(!attr) break;
                    std::cout<<std::setw(indent)<<""<<"enumerator"<<std::endl;
                    indent+=2;
                    attr=dwarf_attr_integrate(&result, DW_AT_name, &attrMem);
                    if(attr) std::cout<<std::setw(indent)<<""<<"name: "<<dwarf_formstring(attr)<<std::endl;
                    attr=dwarf_attr_integrate(&result, DW_AT_const_value, &attrMem);
                    if(attr){
                        Dwarf_Sword a;
                        Dwarf_Word b;
                        if(dwarf_formsdata(attr, &a)) std::cout<<std::setw(indent)<<""<<"value: "<<a<<std::endl;
                        if(dwarf_formudata(attr, &b)) std::cout<<std::setw(indent)<<""<<"value: "<<b<<std::endl;
                    }
                    indent-=2;
                    break;
                default:
                    break;
            }
        }while(!dwarf_siblingof(&result, &result));
    }
    indent-=2;
}
int main(int argc, char **args){
    if(argc!=2) return 1;
    int fd=open(args[1], O_RDONLY, 0);
    if(fd<0) return 2;
    Dwarf *dw=dwarf_begin(fd, DWARF_C_READ);
    if(!dw) return 3;
    Dwarf_Off offset=0, lastOffset=0;
    size_t hdrSize;
    while(dwarf_nextcu(dw, offset, &offset, &hdrSize,0,0,0)==0){
        std::cout<<"Compilation unit"<<std::endl;
        Dwarf_Die result, cuDie;
        if(!dwarf_offdie(dw, lastOffset+hdrSize, &cuDie)){
            std::cout<<"No DIE"<<std::endl;
            continue;
        }
        lastOffset=offset;
        if(dwarf_child(&cuDie, &result)){
            std::cout<<"No Child"<<std::endl;
            continue;
        }
        do{
            switch(dwarf_tag(&result)){
                case DW_TAG_subprogram:
                case DW_TAG_entry_point:
                case DW_TAG_inlined_subroutine:
                    handleFunction(&result);
                    break;
                case DW_TAG_variable:
                    handleVariable(&result);
                    break;
                case DW_TAG_structure_type:
                case DW_TAG_class_type:
                case DW_TAG_union_type:
                    handleStruct(&result);
                    break;
                case DW_TAG_enumeration_type:
                    handleEnum(&result);
                    break;
                default:
                    break;
            }
        }while(!dwarf_siblingof(&result, &result));
        std::cout<<"End compilation unit"<<std::endl;
    }
    dwarf_end(dw);
    return 0;
}
