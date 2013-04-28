#include "vraptor.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <sstream>
using namespace std;
using namespace VRaptor;

class func_compile{

VFunction* fn;
public:

func_compile(){ }
int assign_func(VFunction* vfunc){ fn=vfunc; return 0;}
void type_constexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_nameexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_indexexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_binaryexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_plusexpr(std::ostream&,ExpressionPtr ,SymTable  *); 
void type_minusexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_multexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_divexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_gtexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_geqexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_ltexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_leqexpr(std::ostream&,ExpressionPtr ,SymTable  *);
void type_mmulexpr(std::ostream&,ExpressionPtr ,SymTable  *);
int type_returnstmt( std::ostream&,StmtPtr  ,SymTable  * );
int type_assignstmt(std::ostream&, StmtPtr  ,SymTable  * );
int type_forstmt(std::ostream&,StmtPtr  ,SymTable  * );
int type_pforstmt(std::ostream&,StmtPtr  ,SymTable  * );
int type_whilestmt(std::ostream&,StmtPtr  ,SymTable  * );
int type_ifstmt(std::ostream&,StmtPtr  ,SymTable  * );
int code_cuda_gen(std::ostream& , StmtListPtr  ,SymTable  * );
int code_cuda_parse(std::ostream& , StmtListPtr  ,SymTable  * );
int code_gen(std::ostream&);
};

void func_compile::type_constexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
			     	//ExpressionPtr lexp =lexptr.at(0);
				ConstExprPtr constxptr = std::tr1::static_pointer_cast<ConstExpr>(exp);

					
						
				          std::cout<<constxptr->getIntVal();
					   out<<constxptr->getIntVal();
 return;
}
void func_compile::type_nameexpr(std::ostream& out, ExpressionPtr  exp, SymTable  *sy)
{
			     	//ExpressionPtr lexp =lexptr.at(0);
				NameExprPtr nmexptr = std::tr1::static_pointer_cast<NameExpr>(exp);
				std::cout<<sy->getName(nmexptr->getId());
				out<<"*"<<sy->getName(nmexptr->getId());
 return;
}
void func_compile::type_indexexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
IndexExprPtr inlexptr = std::tr1::static_pointer_cast<IndexExpr>(exp);
				         
						                                  

           								

 									
              					                        std::cout<<sy->getName(inlexptr->getArrayId())<<"[";
									out<<sy->getName(inlexptr->getArrayId())<<"[";
								        ExpressionPtrVector exptrv = inlexptr->getIndices();
									for(int i=0;i<exptrv.size();i++)
									{
									ExpressionPtr exptr=exptrv.at(i);
     									NameExprPtr nmexptr = std::tr1::static_pointer_cast<NameExpr>(exptr);
									std::cout<<sy->getName(nmexptr->getId());
									out<<"*"<<sy->getName(nmexptr->getId());
									if(i<(exptrv.size()-1)){std::cout<<",";out<<",";}
									}
									std::cout<<"]";
									out<<"]";
									
			                                                

return; 
}


void func_compile::type_plusexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
PlusExprPtr  pexptr = std::tr1::static_pointer_cast<PlusExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();
							
                                                        if(lpxptr->isBinaryExpr()){type_binaryexpr( out,lpxptr,sy);}
							std::cout<<" + ";
							out<<" + ";
							if((rpxptr->getExprType())==0){type_constexpr(out,rpxptr,sy);}
					
							if((rpxptr->getExprType())==1){type_nameexpr(out,rpxptr,sy);}
							if((rpxptr->getExprType()==6))
								{
								IndexExprPtr inrexptr = std::tr1::static_pointer_cast<IndexExpr>(rpxptr);
								type_indexexpr(out,inrexptr,sy);
								}

 
return;
}
                                                            
void func_compile::type_minusexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
MinusExprPtr  pexptr = std::tr1::static_pointer_cast<MinusExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();
							
                                                        if(lpxptr->isBinaryExpr()){type_binaryexpr( out,lpxptr,sy);}
							std::cout<<" - ";
							out<<" - ";
							if((rpxptr->getExprType())==0){type_constexpr(out,rpxptr,sy);}
					
							if((rpxptr->getExprType())==1){type_nameexpr(out,rpxptr,sy);}
							if((rpxptr->getExprType()==6))
								{
								IndexExprPtr inrexptr = std::tr1::static_pointer_cast<IndexExpr>(rpxptr);
								type_indexexpr(out,inrexptr,sy);
								}

	    			
 
return;

}
                                                             
void func_compile::type_multexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
MultExprPtr  pexptr = std::tr1::static_pointer_cast<MultExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();
							if(lpxptr->isBinaryExpr()){type_binaryexpr( out,lpxptr,sy);}
							std::cout<<" * ";
							out<<" * ";
							if((rpxptr->getExprType())==0){type_constexpr(out,rpxptr,sy);}
					
							if((rpxptr->getExprType())==1){type_nameexpr(out,rpxptr,sy);}
							if((rpxptr->getExprType()==6))
								{
								IndexExprPtr inrexptr = std::tr1::static_pointer_cast<IndexExpr>(rpxptr);
								type_indexexpr(out,inrexptr,sy);
								}

				
	    			
    
 
return;
}


void func_compile::type_divexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
DivExprPtr  pexptr = std::tr1::static_pointer_cast<DivExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();
							
                                                        if(lpxptr->isBinaryExpr()){type_binaryexpr( out,lpxptr,sy);}
							std::cout<<" / ";
							out<<" / ";
							if((rpxptr->getExprType())==0){type_constexpr(out,rpxptr,sy);}
					
							if((rpxptr->getExprType())==1){type_nameexpr(out,rpxptr,sy);}
							

	    			
    
 
return;
}

void func_compile::type_gtexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
                                                             
GtExprPtr  pexptr = std::tr1::static_pointer_cast<GtExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();

  
 if((lpxptr->getExprType()==0))
					{
						type_constexpr(out,lpxptr,sy);
						std::cout<<" > ";
						out<<" > ";
						if((rpxptr->getExprType()==0))
								{ type_constexpr(out,rpxptr,sy);}
                                        	if((rpxptr->getExprType()==1)){type_nameexpr(out,rpxptr,sy);}
						//std::cout<<";"<<std::endl;
						return;
					}
 

if((lpxptr->getExprType()==1))
				{       	type_nameexpr(out,lpxptr,sy);
						std::cout<<" > ";
						out<<" > ";
						if((rpxptr->getExprType()==0))
								{ type_constexpr(out,rpxptr,sy);}
						if((rpxptr->getExprType()==1)){type_nameexpr(out,rpxptr,sy);}
						
					       // std::cout<<";"<<std::endl;
				}	
return;
}
void func_compile::type_geqexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
                                                             
GeqExprPtr  pexptr = std::tr1::static_pointer_cast<GeqExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();

  
 if((lpxptr->getExprType()==0))
					{
						type_constexpr(out,lpxptr,sy);
						std::cout<<" >= ";
						out<<" >= ";
						if((rpxptr->getExprType()==0))
								{ type_constexpr(out,rpxptr,sy);}
                                        	if((rpxptr->getExprType()==1)){type_nameexpr(out,rpxptr,sy);}
						//std::cout<<";"<<std::endl;
						return;
					}
 

if((lpxptr->getExprType()==1))
				{       	type_nameexpr(out,lpxptr,sy);
						std::cout<<" >= ";
						out<<" >= ";
						if((rpxptr->getExprType()==0))
								{ type_constexpr(out,rpxptr,sy);}
						if((rpxptr->getExprType()==1)){type_nameexpr(out,rpxptr,sy);}
						
					        //std::cout<<";"<<std::endl;
				}	
return;
}
void func_compile::type_ltexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
                                                             
LtExprPtr  pexptr = std::tr1::static_pointer_cast<LtExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();

  
 if((lpxptr->getExprType()==0))
					{
						type_constexpr(out,lpxptr,sy);
						std::cout<<" < ";
						out<<" < ";
						if((rpxptr->getExprType()==0))
								{ type_constexpr(out,rpxptr,sy);}
                                        	if((rpxptr->getExprType()==1)){type_nameexpr(out,rpxptr,sy);}
						//std::cout<<";"<<std::endl;
						return;
					}
 

if((lpxptr->getExprType()==1))
				{       	type_nameexpr(out,lpxptr,sy);
						std::cout<<" < ";
						out<<" < ";
						if((rpxptr->getExprType()==0))
								{ type_constexpr(out,rpxptr,sy);}
						if((rpxptr->getExprType()==1)){out,type_nameexpr(out,rpxptr,sy);}
						
					       // std::cout<<";"<<std::endl;
				}	
return;
}
void func_compile::type_leqexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
                                                             
LeqExprPtr  pexptr = std::tr1::static_pointer_cast<LeqExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();

  
 if((lpxptr->getExprType()==0))
					{
						type_constexpr(out,lpxptr,sy);
						std::cout<<" <= ";
						out<<" <= ";
						if((rpxptr->getExprType()==0))
								{ type_constexpr(out,rpxptr,sy);}
                                        	if((rpxptr->getExprType()==1)){type_nameexpr(out,rpxptr,sy);}
						//std::cout<<";"<<std::endl;
						return;
					}
 

if((lpxptr->getExprType()==1))
				{       	type_nameexpr(out,lpxptr,sy);
						std::cout<<" <= ";
						out<<" <= ";
						if((rpxptr->getExprType()==0))
								{ type_constexpr(out,rpxptr,sy);}
						if((rpxptr->getExprType()==1)){type_nameexpr(out,rpxptr,sy);}
						
					        //std::cout<<";"<<std::endl;
				}	
return;
}
void func_compile::type_mmulexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{MmultExprPtr  pexptr = std::tr1::static_pointer_cast<MmultExpr>(exp);
		ExpressionPtr  rpxptr	=pexptr->getRhs();
		ExpressionPtr  lpxptr	=pexptr->getLhs();
							
                                                        if((lpxptr->getExprType()==6))
								{
								IndexExprPtr inrexptr = std::tr1::static_pointer_cast<IndexExpr>(lpxptr);
								type_indexexpr(out,inrexptr,sy);
								}
							std::cout<<" * ";
							out<<" * ";
							if((rpxptr->getExprType()==6))
								{
								IndexExprPtr inrexptr = std::tr1::static_pointer_cast<IndexExpr>(rpxptr);
								type_indexexpr(out,inrexptr,sy);
								}

return;
}
void func_compile::type_binaryexpr(std::ostream& out,ExpressionPtr  exp, SymTable  *sy)
{
 //BinaryExprPtr bexptr = std::tr1::static_pointer_cast<BinaryExpr>(exp);

 BinaryExprPtr bexptr = std::tr1::static_pointer_cast<BinaryExpr>(exp);
					         
		ExpressionPtr  brpxptr	=bexptr->getRhs();
		ExpressionPtr  blpxptr	=bexptr->getLhs();
				//std::cout<<"binary";
			       
				if((bexptr->getExprType()==2)){
								if((blpxptr->getExprType())==0){type_constexpr(out,blpxptr,sy);}
								if((blpxptr->getExprType())==1){type_nameexpr(out,blpxptr,sy);}
								if((blpxptr->getExprType()==6))
								{
								IndexExprPtr inlexptr = std::tr1::static_pointer_cast<IndexExpr>(blpxptr);
								type_indexexpr(out,inlexptr,sy);
								}
								
								   type_plusexpr(out,bexptr,sy);				

							        }

				if((bexptr->getExprType()==3)){
								if((blpxptr->getExprType())==0){type_constexpr(out,blpxptr,sy);}
								if((blpxptr->getExprType())==1){type_nameexpr(out,blpxptr,sy);}
								if((blpxptr->getExprType()==6))
								{
								IndexExprPtr inlexptr = std::tr1::static_pointer_cast<IndexExpr>(blpxptr);
								type_indexexpr(out,inlexptr,sy);
								}
								
								   type_minusexpr(out,bexptr,sy);				

							        }
				if((bexptr->getExprType()==4)){ //std::cout<<"u r here in mult";
								if((blpxptr->getExprType())==0){type_constexpr(out,blpxptr,sy);}
								if((blpxptr->getExprType())==1){type_nameexpr(out,blpxptr,sy);}
								if((blpxptr->getExprType()==6))
								{
								IndexExprPtr inlexptr = std::tr1::static_pointer_cast<IndexExpr>(blpxptr);
								type_indexexpr(out,inlexptr,sy);
								}						
								   type_multexpr(out,bexptr,sy);				

							        }


				if((bexptr->getExprType()==5)){
								if((blpxptr->getExprType())==0){type_constexpr(out,blpxptr,sy);}
								if((blpxptr->getExprType())==1){type_nameexpr(out,blpxptr,sy);}
														
								   type_divexpr(out,bexptr,sy);				

							        }
				if((bexptr->getExprType()==8)){ //std::cout<<"u r here";
								if((blpxptr->getExprType()==6))
								{
								IndexExprPtr inlexptr = std::tr1::static_pointer_cast<IndexExpr>(blpxptr);
								type_indexexpr(out,inlexptr,sy);
								}
														
								   type_mmulexpr(out,bexptr,sy);				

							        }
					
				

							if((bexptr->getExprType()==10))
								{
								   type_gtexpr(out,bexptr,sy);
								}
							if((bexptr->getExprType()==11))
								{
								   type_geqexpr(out,bexptr,sy);
								}
							if((bexptr->getExprType()==12))
								{
								   type_ltexpr(out,bexptr,sy);
								}
							if((bexptr->getExprType()==13))
								{
								   type_leqexpr(out,bexptr,sy);
								}

												


return;
}
int func_compile::type_returnstmt(std::ostream& out,StmtPtr s_ptr, SymTable *sy_ptr)
{      
  std::vector<int> symid= sy_ptr->getAllIds();
         
             ReturnStmtPtr  rstmptr=std::tr1::static_pointer_cast<ReturnStmt>(s_ptr);
							   
							   std::vector<int>  rrid =   rstmptr->getRids();
                                                            if(rrid.size()!=0){ 
							     
                                                             int id=rrid[0];
							//    std::cout<<'\t'<< id <<"  " << sy->getName(symid.at(id))<<std::endl;
							      std::cout<<"return "<< sy_ptr->getName(symid.at(id))<<" ; " << std::endl <<"}"<<std::endl;
                                                              out<<"return "<< sy_ptr->getName(symid.at(id))<<" ; " << std::endl <<"}"<<std::endl; 
                                                           }
						else {std::cout<<"return "<<" ; " << std::endl <<"}"<<std::endl;
						       out<<"return "<<" ; " << std::endl <<"}"<<std::endl;}
return 0;



}

int func_compile::type_assignstmt(std::ostream& out,StmtPtr s_ptr, SymTable *sy_ptr){
                                                     //assignment statement

       									 
                    AssignStmtPtr asmptr = std::tr1::static_pointer_cast<AssignStmt>(s_ptr);
                                                        
                    ExpressionPtr rexptr= asmptr->getRhs();
                    std::vector<ExpressionPtr>  lexptr =  asmptr->getLhs();
							
						
                                                          
		    if(lexptr.at(0)->getExprType()==1){
								ExpressionPtr lexp =lexptr.at(0);
								type_nameexpr(out,lexp,sy_ptr);
								std::cout<<" = ";
								out<<" = ";
							}
     			if(lexptr.at(0)->getExprType()==6)       
							{      
									ExpressionPtr lexp =lexptr.at(0);
                                                                        type_indexexpr(out,lexp,sy_ptr);
					 			        std::cout<<" = ";
									out<<" = ";
							}
			if(rexptr->isBinaryExpr())
						{ //std::cout<<"u are here:";
						 type_binaryexpr(out,rexptr, sy_ptr);
								
					        	std::cout<<";";
							out<<";";
						
					   	}
														
								if((rexptr->getExprType()==0))
								{
							type_constexpr(out,rexptr, sy_ptr);
								std::cout<<";";	
									out<<";";								
								}
																				
							
							if((rexptr->getExprType()==1))
								{
							type_nameexpr(out,rexptr, sy_ptr);
								std::cout<<";";	
									out<<";";								
								}
							if((rexptr->getExprType()==6))
								{
									type_indexexpr(out,rexptr, sy_ptr);
									std::cout<<";";	
									out<<";";							
								}
							
							 


std::cout<<endl;
out<<endl;
return 0;
}

int func_compile::type_ifstmt(std::ostream& out,StmtPtr s_ptr, SymTable *sy_ptr)
{


IfStmtPtr ifstmptr = std::tr1::static_pointer_cast<IfStmt>(s_ptr);
ExpressionPtr ifexprptr= ifstmptr->getCond();
		std::cout<<"if( ";
		out<<"if( ";
          if(ifexprptr->isBinaryExpr()){type_binaryexpr(out,ifexprptr, sy_ptr);}
		std::cout<<"){ "<<std::endl;
		out<<"){ "<<std::endl;

StmtPtr ifbranch=ifstmptr->getIfBranch(); 

			                    {    
						      StmtListPtr stmlpt = std::tr1::static_pointer_cast<StmtList>(ifbranch);
						      size_t  xy= stmlpt->getNumChildren() ; 
							//std::cout<<"no of statements :"<< xy << "    "<<std::endl;
                                                      for(int i=0;i<xy;i++)
							{
							 StmtPtr stmptr=stmlpt->getChild(i); 
							 if((stmptr->getStmtType())==0)
								{
								int k= type_assignstmt(out,stmptr,sy_ptr);
								}
							
							if((stmptr->getStmtType())==3)
								{
								int k= type_forstmt(out,stmptr,sy_ptr);
								}
 
	         					}
					      }



		std::cout<<"}";
		out<<" }";
if (ifstmptr->hasElseBranch()){

StmtPtr elsebranch = ifstmptr->getElseBranch();
std::cout<<"else { "<<std::endl;
		out<<"else{ "<<std::endl;
			                {    
						      StmtListPtr stmlpt = std::tr1::static_pointer_cast<StmtList>(elsebranch);
						      size_t  xy= stmlpt->getNumChildren() ; 
							//std::cout<<"no of statements :"<< xy << "    "<<std::endl;
                                                      for(int i=0;i<xy;i++)
							{
							 StmtPtr stmptr=stmlpt->getChild(i); 
							 if((stmptr->getStmtType())==0)
								{
								int k= type_assignstmt(out,stmptr,sy_ptr);
								}
							
							if((stmptr->getStmtType())==3)
								{
								int k= type_forstmt(out,stmptr,sy_ptr);
								}
 
	         					}
					      }
		std::cout<<"}";
		out<<" }";




}
						




return 0;
}

int func_compile::type_whilestmt(std::ostream& out,StmtPtr s_ptr, SymTable *sy_ptr)
{
WhileStmtPtr  wstmptr = std::tr1::static_pointer_cast<WhileStmt>(s_ptr);


	std::cout<<"while(";
	out<<"while(";
	ExpressionPtr wcondptr=wstmptr->getCond(); 

	  if(wcondptr->isBinaryExpr()){type_binaryexpr(out,wcondptr, sy_ptr);}
	std::cout<<" ){" <<std::endl;
	out<<" ){" <<std::endl;
	
	StmtPtr   wstmt= wstmptr->getBody();
         
						 {    
						      StmtListPtr stmlpt = std::tr1::static_pointer_cast<StmtList>(wstmt);
						      size_t  xy= stmlpt->getNumChildren() ; 
							//std::cout<<"no of statements :"<< xy << "    "<<std::endl;
                                                      for(int i=0;i<xy;i++)
							{
							 StmtPtr stmptr=stmlpt->getChild(i); 
							 if((stmptr->getStmtType())==0)
								{
								int k= type_assignstmt(out,stmptr,sy_ptr);
								}
							
							if((stmptr->getStmtType())==3)
								{
								int k= type_forstmt(out,stmptr,sy_ptr);
								}
							if((stmptr->getStmtType())==1)
								{ std::cout<<"we are here";
								int k= type_ifstmt(out,stmptr,sy_ptr);
								}
 
	         					}
						}
	std::cout<<"}";
	out<<"}";



	



return 0;
}



 int func_compile::type_forstmt(std::ostream& out,StmtPtr s_ptr, SymTable *sy_ptr)
{//for  stmt
		 ForStmtPtr  fstmptr = std::tr1::static_pointer_cast<ForStmt>(s_ptr);
                 ExpressionPtr fexptr= fstmptr->getDomain();
		 int forstart,forstep;
		 std::string forstop;  
		 int dimension;
					
		  
			if((fexptr->getExprType())==18)
			{

							                 		
				 DomainExprPtr dexptr= std::tr1::static_pointer_cast<DomainExpr>(fexptr);
			         dimension= dexptr->getNdims();
					
					for(int i=0;i<dimension;i++){					
					  ExpressionPtr  start_exptr= dexptr->getStartExpr(i);	
              				  ExpressionPtr step_exptr= dexptr->getStepExpr(i);
   					  ExpressionPtr stop_exptr= dexptr->getStopExpr(i);
						  if((start_exptr->getExprType())==0)
							{  
								ConstExprPtr  cexptr = std::tr1::static_pointer_cast<ConstExpr>(start_exptr);
								 forstart =cexptr->getIntVal();
								
							}
						if((step_exptr->getExprType())==0)
							{
   							     
							      ConstExprPtr  cexptr = std::tr1::static_pointer_cast<ConstExpr>(step_exptr);
     								 forstep=cexptr->getIntVal();
								
							}
					        if((stop_exptr->getExprType())==1)
							{									 						     
							 NameExprPtr cexptr = std::tr1::static_pointer_cast<NameExpr>(stop_exptr);	
	                                                 forstop=sy_ptr->getName(cexptr->getId());			
		   						
							}
				std::vector<int> iterv =  fstmptr->getIterVars();
                               
              //for(int i=0;i<iterv.size();i++)
		 std::cout<<" for("<<sy_ptr->getName(iterv.at(i)) <<" =  "<<forstart<<"; "<< sy_ptr->getName(iterv.at(i)) << "< " << forstop <<" ; "<<sy_ptr->getName(iterv.at(i))<<" = " << sy_ptr->getName(iterv.at(i))<<"+" << forstep << " )"<<std::endl;
			out<<" for("<<"*"<<sy_ptr->getName(iterv.at(i)) <<" =  "<<forstart<<"; "<<"*"<< sy_ptr->getName(iterv.at(i)) << "< " << "*"<<forstop <<" ; "<<"*"<<sy_ptr->getName(iterv.at(i))<<" = " <<"*" <<sy_ptr->getName(iterv.at(i))<<"+" << forstep << " )"<<std::endl;
   		 std::cout<<"{ " <<std::endl;	
		 out<<"{ " <<std::endl;	
	
					}
			}
	    
               
             					

    		                      StmtPtr  fstmt = fstmptr->getBody();
 					{
						    
						      StmtListPtr stmlpt = std::tr1::static_pointer_cast<StmtList>(fstmt);
						      size_t  xy= stmlpt->getNumChildren() ; 
							
                                                      for(int i=0;i<xy;i++)
							{
							 StmtPtr stmptr=stmlpt->getChild(i); 
							 if((stmptr->getStmtType())==0)
								{
								int k= type_assignstmt(out,stmptr,sy_ptr);
								//std::cout<<";";
								
								}
							if((stmptr->getStmtType())==3){int k= type_forstmt(out,stmptr,sy_ptr);}
							if((stmptr->getStmtType())==2)
								{
								int k= type_whilestmt(out,stmptr,sy_ptr);
								}

 
	         					}
               				}
               for(int i=0;i<dimension;i++)
   		{std::cout<<std::endl<<"}"<<std::endl;
		out<<std::endl<<"}"<<std::endl;}
	return 0;                      
}
int func_compile::type_pforstmt(std::ostream& out,StmtPtr s_ptr, SymTable *sy_ptr)
{//for  stmt
		 PforStmtPtr  fstmptr = std::tr1::static_pointer_cast<PforStmt>(s_ptr);
                 ExpressionPtr fexptr= fstmptr->getDomain();
		 int forstart,forstep;
		 std::string forstop;  
		 int dimension;
					
		  
			if((fexptr->getExprType())==18)
			{

							                 		
				 DomainExprPtr dexptr= std::tr1::static_pointer_cast<DomainExpr>(fexptr);
			         dimension= dexptr->getNdims();
					
					for(int i=0;i<dimension;i++){					
					  ExpressionPtr  start_exptr= dexptr->getStartExpr(i);	
              				  ExpressionPtr step_exptr= dexptr->getStepExpr(i);
   					  ExpressionPtr stop_exptr= dexptr->getStopExpr(i);
						  if((start_exptr->getExprType())==0)
							{  
								ConstExprPtr  cexptr = std::tr1::static_pointer_cast<ConstExpr>(start_exptr);
								 forstart =cexptr->getIntVal();
								
							}
						if((step_exptr->getExprType())==0)
							{
   							     
							      ConstExprPtr  cexptr = std::tr1::static_pointer_cast<ConstExpr>(step_exptr);
     								 forstep=cexptr->getIntVal();
								
							}
					        if((stop_exptr->getExprType())==1)
							{									 						     
							 NameExprPtr cexptr = std::tr1::static_pointer_cast<NameExpr>(stop_exptr);	
	                                                 forstop=sy_ptr->getName(cexptr->getId());			
		   						
							}
				std::vector<int> iterv =  fstmptr->getIterVars();
                               
              //for(int i=0;i<iterv.size();i++)
		 std::cout<<" for("<<sy_ptr->getName(iterv.at(i)) <<" =  "<<forstart<<"; "<< sy_ptr->getName(iterv.at(i)) << "< " << forstop <<" ; "<<sy_ptr->getName(iterv.at(i))<<" = " << sy_ptr->getName(iterv.at(i))<<"+" << forstep << " )"<<std::endl;
			out<<" for("<<"*"<<sy_ptr->getName(iterv.at(i)) <<" =  "<<forstart<<"; "<<"*"<< sy_ptr->getName(iterv.at(i)) << "< " << "*"<<forstop <<" ; "<<"*"<<sy_ptr->getName(iterv.at(i))<<" = " <<"*" <<sy_ptr->getName(iterv.at(i))<<"+" << forstep << " )"<<std::endl;
   		 std::cout<<"{ " <<std::endl;	
		 out<<"{ " <<std::endl;	
	
					}
			}
	    
               
             					

    		                      StmtPtr  fstmt = fstmptr->getBody();
 					{
						    
						      StmtListPtr stmlpt = std::tr1::static_pointer_cast<StmtList>(fstmt);
						      size_t  xy= stmlpt->getNumChildren() ; 
							
                                                      for(int i=0;i<xy;i++)
							{
							 StmtPtr stmptr=stmlpt->getChild(i); 
							 if((stmptr->getStmtType())==0)
								{
								int k= type_assignstmt(out,stmptr,sy_ptr);
								//std::cout<<";";
								
								}
							if((stmptr->getStmtType())==3){int k= type_forstmt(out,stmptr,sy_ptr);}
							if((stmptr->getStmtType())==2)
								{
								int k= type_whilestmt(out,stmptr,sy_ptr);
								}

 
	         					}
               				}
               for(int i=0;i<dimension;i++)
   		{std::cout<<std::endl<<"}"<<std::endl;
		out<<std::endl<<"}"<<std::endl;}
	return 0;                      
}
int func_compile::code_cuda_parse(std::ostream& out,StmtListPtr  stlptr ,SymTable *sy_ptr)
{

           size_t  x= stlptr->getNumChildren() ; 
           for(int k= 0; k<x;k++)
  			 {  
			    StmtPtr stmptr=stlptr->getChild(k);
           
			 
              		
			if((stmptr->getStmtType())==4){ return 1;}

			
			
			}
  

}



int func_compile::code_cuda_gen(std::ostream& out,StmtListPtr  stlptr ,SymTable *sy_ptr)
{

           size_t  x= stlptr->getNumChildren() ; 
           for(int k= 0; k<x;k++)
  			 {  
			    StmtPtr stmptr=stlptr->getChild(k);
           
			 if((stmptr->getStmtType())==0){int k= type_assignstmt(out,stmptr,sy_ptr);}
              		 /*if((stmptr->getStmtType())==9){ //return stmt
							//std::cout<<"return callin"; 
						     int k= type_returnstmt(out,stmptr,sy_ptr);
												
							}*/
			if((stmptr->getStmtType())==3){int k= type_forstmt(out,stmptr,sy_ptr);}
			if((stmptr->getStmtType())==4){int k= type_pforstmt(out,stmptr,sy_ptr);}
			if((stmptr->getStmtType())==2){int k= type_whilestmt(out,stmptr,sy_ptr);}
			if((stmptr->getStmtType())==1){int k= type_ifstmt(out,stmptr,sy_ptr);}
			}
  

}



int func_compile::code_gen(std::ostream& out ){

  
        int argnum= fn->m_args.size();
      // for(int  a=0;a< argnum;a++){ std::cout<<fn->m_args[a].m_id;} 
 	SymTable *sy=fn->getSymTable();
        std::cout<<std::endl<<' '<<"symbol table size"<< sy->getSize()<<std::endl;
        std::cout<<"-----------------symtable contents------------"<<std::endl;
        std::vector<int> symid= sy->getAllIds();
                    
        for (unsigned i=0; i<symid.size(); i++)
          {
           VTypePtr v= sy->getType(symid.at(i));
           std::string s= sy->getName(symid.at(i));
           std::cout<< ' ' << symid.at(i)<< ' '<< s << ' '<< v->getBasicType() <<'\n';
          }
		
			StmtListPtr stmtlp= fn->getBody();
			out<<"#include <iostream>"<<std::endl<<"#include <cuda.h>"<<std::endl<<"__global__ void mykernel(";
			{
				for(int x=0;x<sy->getSize();x++)
				{  VTypePtr v= sy->getType(symid.at(x));
				 switch(v->getBasicType()){
	                         case 0: {    ScalarTypePtr  scalarptr = std::tr1::static_pointer_cast<ScalarType>(v);  
						switch(scalarptr->getScalarTag())
						{
						case 0: {out<<" int " <<"*"<<sy->getName(symid.at(x));
							break;}
						case 1: {out<<" float " <<"*"<<sy->getName(symid.at(x));
							break;}
						default:;
						}
					 break;
					 }
				 case 2: {     ArrayTypePtr  arrayptr = std::tr1::static_pointer_cast<ArrayType>(v); 
  						
						ScalarTypePtr  scalarptr=arrayptr->getElementType();
						
						switch(scalarptr->getScalarTag())
						{
						case 0: {out<<" int " <<sy->getName(symid.at(x))<<"[]";
								
							
								break;}
						case 1: {out<<" float " <<sy->getName(symid.at(x))<<"[]";
							break;}
						default:;
						}
					  break;
					  }
				 default: ;
	                          }
				if(x<(sy->getSize()-1)){out<<",";}
				}
			}
			out<<")";
			out<<std::endl<<"{"<<std::endl;
			code_cuda_gen(out,stmtlp,sy);
                        out<<"}";
			out<<std::endl<<"int  main() { "<<std::endl;
                                            
			for(int x=0;x<sy->getSize();x++){  VTypePtr v= sy->getType(symid.at(x));
			 switch(v->getBasicType()){
                         case 0:{   ScalarTypePtr  scalarptr = std::tr1::static_pointer_cast<ScalarType>(v);  
						switch(scalarptr->getScalarTag())
						{
						case 0: {out<<" int " <<sy->getName(symid.at(x))<<";";
							break;}
						case 1: {out<<" float " <<sy->getName(symid.at(x))<<";";
							break;}
						default:;
						}
					 break;
				}
			case 2: {     ArrayTypePtr  arrayptr = std::tr1::static_pointer_cast<ArrayType>(v); 
  						
						ScalarTypePtr  scalarptr=arrayptr->getElementType();
						
						switch(scalarptr->getScalarTag())
						{
						case 0: {out<<"int* " <<sy->getName(symid.at(x))<<" = NULL ;"<<std::endl;
								
							
								break;}
						case 1: {out<<"float* " <<sy->getName(symid.at(x))<<" =NULL;"<<std::endl;
							break;}
						default:;
						}
					  break;
					  }		 
			 	 
			 default: ;
                          }
		}
			
                out<<std::endl;
			 for(int x=0;x<sy->getSize();x++)
			{  
				VTypePtr v= sy->getType(symid.at(x));
			 	switch(v->getBasicType())
				{
                         	case 0: {   ScalarTypePtr  scalarptr = std::tr1::static_pointer_cast<ScalarType>(v);  
						switch(scalarptr->getScalarTag())
						{
						case 0: { out<<"int " <<"*"  <<"d_"<<sy->getName(symid.at(x)) << ";"<<std::endl;
							break;}
						case 1: { out<<"float " <<"*"  <<"d_"<<sy->getName(symid.at(x)) << ";"<<std::endl;
							break;}
						default:;
						}
					 break;
				}
				 
			 default: ;
                         }
		}
			


	      for(int  a=0;a< argnum;a++){ VTypePtr v= sy->getType(symid.at(a));
		switch(v->getBasicType()){
                         case 0: { out<<"std::cout<<"<<"\""<<"enter the value of " ;
				   out<<sy->getName(fn->m_args[a].m_id)<<"\" "<<";"<<std::endl ;
				   out<<"std::cin >>"<<sy->getName(fn->m_args[a].m_id)<<";"<<std::endl;
				  }
			default:;
		} 
		}
		
		
		for(int x=0;x<sy->getSize();x++){  VTypePtr v= sy->getType(symid.at(x));
			 switch(v->getBasicType()){
                         
			case 2: {     ArrayTypePtr  arrayptr = std::tr1::static_pointer_cast<ArrayType>(v); 
  						
						ScalarTypePtr  scalarptr=arrayptr->getElementType();
						
						switch(scalarptr->getScalarTag())
						{
						case 0: {out<<sy->getName(symid.at(x))<<" = new "<< "int[n];"<<std::endl;
								
							
								break;}
						case 1: {out<<sy->getName(symid.at(x))<<" =new "<<"float[n];"<<std::endl;
							break;}
						default:;
						}
					  break;
					  }		 
			 	 
			 default: ;
                          }
		}

		for(int  a=0;a< argnum;a++){ VTypePtr v= sy->getType(symid.at(a));
		switch(v->getBasicType()){
                         case 2: { out<<"std::cout<<"<<"\""<<"enter the value of  array " ;
				   out<<sy->getName(fn->m_args[a].m_id)<<"\" "<<";"<<std::endl ;

				   out<<"for(int i=0;i<n;i++){"<<std::endl;
				   out<<"std::cin >>"<<sy->getName(fn->m_args[a].m_id)<<"[i]"<<";"<<std::endl<<"}"<<std::endl;
				  }
			default:;
		} 
		}



		//out<<"int size_"<<"0 "<<"= sizeof(int);"<<std::endl;
		//out<<"float size_"<<"1 "<<"= sizeof(float);"<<std::endl;

	    // out<<"int size = sizeof(int); "<< std::endl;	
	     
		for(int x=0;x<sy->getSize();x++){  VTypePtr v= sy->getType(symid.at(x));
			 switch(v->getBasicType()){
                         case 0:{     ScalarTypePtr  scalarptr = std::tr1::static_pointer_cast<ScalarType>(v);  
						switch(scalarptr->getScalarTag())
						{
						case 0: { 
							out<<"cudaMalloc((void **)" <<"&d_"<<sy->getName(symid.at(x)) <<","<<"sizeof(int) )"<<";"<<std::endl;
							break;}
						case 1: { 
							out<<"cudaMalloc((void **)" <<"&d_"<<sy->getName(symid.at(x)) <<","<<"sizeof(float)"<<";"<<std::endl;
							break;}
						default:;
						}
					 break;
					
				 }
			 case 2: {     ArrayTypePtr  arrayptr = std::tr1::static_pointer_cast<ArrayType>(v); 
  						
						ScalarTypePtr  scalarptr=arrayptr->getElementType();
						
						switch(scalarptr->getScalarTag())
						{
						case 0: { 
							out<<"cudaMalloc((void **)" <<"&d_"<<sy->getName(symid.at(x)) <<","<<"sizeof(int )"<<";"<<std::endl;
							break;}
						case 1: { 
							out<<"cudaMalloc((void **)" <<"&d_"<<sy->getName(symid.at(x)) <<","<<"sizeof(float)"<<";"<<std::endl;
							break;}

						default:;
						}
					  break;
					  }		 
			 	 
			 default: ;
                          }
		}

	    
		for(int x=0;x<sy->getSize();x++){  VTypePtr v= sy->getType(symid.at(x));
			 switch(v->getBasicType()){
                         case 0: {     ScalarTypePtr  scalarptr = std::tr1::static_pointer_cast<ScalarType>(v);  
						switch(scalarptr->getScalarTag())
						{
						case 0: { 
				out<<"cudaMemcpy(" <<"d_"<<sy->getName(symid.at(x)) <<","<<"&"<<sy->getName(symid.at(x))<<", sizeof(int), cudaMemcpyHostToDevice );"<<std::endl;
							break;}
						case 1: { 
				out<<"cudaMemcpy(" <<"d_"<<sy->getName(symid.at(x)) <<","<<"&"<<sy->getName(symid.at(x))<<", sizeof(float), cudaMemcpyHostToDevice );"<<std::endl;
							break;}
						default:;
						}
					 break;
					
				 }
				 
			 case 2: {     ArrayTypePtr  arrayptr = std::tr1::static_pointer_cast<ArrayType>(v); 
  						
						ScalarTypePtr  scalarptr=arrayptr->getElementType();
						
						switch(scalarptr->getScalarTag())
						{
						case 0: { 
							out<<"cudaMemcpy(" <<"d_"<<sy->getName(symid.at(x)) <<","<<sy->getName(symid.at(x))<<", sizeof(int), cudaMemcpyHostToDevice );"<<std::endl;
							break;}
						case 1: { 
							out<<"cudaMemcpy(" <<"d_"<<sy->getName(symid.at(x)) <<","<<sy->getName(symid.at(x))<<", sizeof(float), cudaMemcpyHostToDevice );"<<std::endl;
							break;}

						default:;
						}
					  break;
					  }	
			 default:;
                          }
			}

	    out<<std::endl;
             	if((code_cuda_parse(out,stmtlp,sy)==1)){ out<<" mykernel<<<1,2>>>(";}
                else{out<<" mykernel<<<1,1>>>(";}
 
		for(int x=0;x<sy->getSize();x++)

			{ 
				out<<"d_"<<sy->getName(symid.at(x));
				if(x<(sy->getSize()-1)){out<<",";}
			}
		out<<");"<<std::endl;
                out<<std::endl;

       
for(int x=0;x<sy->getSize();x++){  VTypePtr v= sy->getType(symid.at(x));
			 switch(v->getBasicType()){
                         case 0: {     ScalarTypePtr  scalarptr = std::tr1::static_pointer_cast<ScalarType>(v);  
						switch(scalarptr->getScalarTag())
						{
						case 0: { 
				out<<"cudaMemcpy(" <<"&"<<sy->getName(symid.at(x)) <<","<<"d_"<<sy->getName(symid.at(x))<<", sizeof(int), cudaMemcpyDeviceToHost );"<<std::endl;
							break;}
						case 1: { 
				out<<"cudaMemcpy(" <<"&"<<sy->getName(symid.at(x)) <<","<<"d_"<<sy->getName(symid.at(x))<<", sizeof(float), cudaMemcpyDeviceToHost );"<<std::endl;
							break;}
						default:;
						}
					 break;
					
				 }
				 
			 case 2: {     ArrayTypePtr  arrayptr = std::tr1::static_pointer_cast<ArrayType>(v); 
  						
						ScalarTypePtr  scalarptr=arrayptr->getElementType();
						
						switch(scalarptr->getScalarTag())
						{
						case 0: { 
							out<<"cudaMemcpy(" <<sy->getName(symid.at(x)) <<","<<"d_"<<sy->getName(symid.at(x))<<", sizeof(int), cudaMemcpyDeviceToHost );"<<std::endl;
							break;}
						case 1: { 
							out<<"cudaMemcpy(" <<sy->getName(symid.at(x)) <<","<<"d_"<<sy->getName(symid.at(x))<<", sizeof(float), cudaMemcpyDeviceToHost );"<<std::endl;
							break;}

						default:;
						}
					  break;
					  }	
			 default:;
                          }
			}

			
			
			 for(int x=0;x<sy->getSize();x++){  VTypePtr v= sy->getType(symid.at(x));
			 switch(v->getBasicType()){
                         case 2: out<<"Free( "<<sy->getName(symid.at(x)) << " );"<<std::endl;
			 	 
			 default: ;
                          }
			}
                    
			
			 for(int x=0;x<sy->getSize();x++){  VTypePtr v= sy->getType(symid.at(x));
			 switch(v->getBasicType()){
                         case 0:{ out<<"cudaFree( "<<"d_"<<sy->getName(symid.at(x)) << " );"<<std::endl;break;}
			 case 2: {out<<"cudaFree( "<<"d_"<<sy->getName(symid.at(x)) << " );"<<std::endl; break;}
			 default: ;
                          }
			}


	     
		

out<<"return 0 ;"<<std::endl<<"}";
}
		 
           



string readFile(const string& fname){
	ifstream f(fname.c_str());
	stringstream buf;
	while(f.good()){
		string line;
		getline(f,line);
		buf<<line<<endl;
	}	
	f.close();
	return buf.str();
}


string IntToStr(int n) 
{
    stringstream result;
    result << n;
    return result.str();
}


int main(int argc,char **argv)
{       string filename;
	string fname(argv[1]);
	string s = readFile(fname);
	VModule *m = VModule::readFromString(s);
        vector<func_compile> func;
        //cout<<endl<<m->m_funcs.size()<<"   Read file"<<endl;
        
        for(int i=0;i<m->m_funcs.size();i++)
   		{              filename="file_" + IntToStr(i) +".cu";
			       std::ofstream outFile(filename.c_str());
			       func_compile   funt;
			
                               funt.assign_func(m->m_funcs.at(i));
			       funt.code_gen(outFile);
			       
	 
                            
			     				
		}    
                        
         

return 0;
         
}
  


